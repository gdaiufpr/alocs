#include "alocs_conf.h"
#include "storage_types.h"
#include "iceph.h"
#include "msg_service_req.h"
#include "up_queue.h"
#include "ccontrol_types.h"

#ifndef STORAGE_H
#define STORAGE_H

//obtem a posicao do slot livre obtido a partir do bitmap
#define GET_SLOT_POS(p,k) ((p * SLOT_SIZE)+ k)
//posicao do offset no slot
#define OFF_POS_SLOT(s) (s)
//posicao do length no slot
#define LEN_POS_SLOT(s) (s+4)
//posicao de key no slot
#define KEY_POS_SLOT(s) (s+8)

//#define MBITS_OFFSET() (BYTES_LIMIT + LOCK_FLAG_SIZE)


/***********************************************
DEFINICAO FUNCOES DE GERENCIAMENTO
************************************************/

/*prototipo: init_ssystem()
 * descricao: inicializa o sistema de armazenamento
 * parametros: */
int init_ssystem(void);

/*prototipo: fin_ssystem()
 * descricao: finaliza o sistema de armazenamento
 * parametros: */
int fin_ssystem(void);

/*prototipo: int check_queue(TSTAMP_T idTx,TSTAMP_T tstamp,LOCAL_T *local,BUCKET_T *data)
 * descricao: verifica se há atualizacoes pendentes na fila,
 * parametros: */
int check_queue(TSTAMP_T idTx,TSTAMP_T tstamp,LOCAL_T *local,BUCKET_T *data);

/*prototipo: int find_max_version(rados_ioctx_t **io_ctx,char *id_bucket,TSTAMP_T **max_version,char **obj_id)
 * descricao: esta funcao busca o bucket com a maior versão, dentro de um namespace
              o namespace é uma divisão logica dentro do pool identificada pelo ib_bucket.
							O id dos objetos no ceph para o alocs é formado por idbucket+version
 * parametros: */
int find_max_version(rados_ioctx_t *io_ctx,char *id_bucket,TSTAMP_T *max_version,char *obj_id);

/**********************************
DEFINICAO OPERACOES INTERFACE S.A.
**********************************/
/*prototipo: int get_bucket(TSTAMP_T,TSTAMP_T,LOCAL_T*,int,LINE_T**)
 *objetivo: Retorna um Bucket, de um Diretorio e Servidor especificados nos parametros de entrada*/
CACHE_GET_RET_T get_bucket(TSTAMP_T idTx,TSTAMP_T tstamp,LOCAL_T *local,int requires_locking,LINE_T **line);

/*prototipo: int get_key(TSTAMP_T,TSTAMP_T,LOCAL_T*,KEY_T,PAIR_T**)
 *objetivo: Retorna o valor associado a chave key*/
int get_key(TSTAMP_T idTx,TSTAMP_T tstamp,LOCAL_T* local,KEY_T key,PAIR_T** pair);

/*objetivo: adicionar um par chave-valor no bucket passado por parametro
 prototipo: int ss_put_data(LOCAL_T,TSTAMP_T,KEY_T,char*)*/
int put_data(TSTAMP_T idTx,LOCAL_T *local,TSTAMP_T tstamp,KEY_T key,char *value);

/*prototipo: int ss_remove_pair(TSTAMP_T,LOCAL_T*,TSTAMP_T,KEY_T)
 *objetivo: Remove um par chave-valor do Bucket correspondente ao identificador passado como parametro
 *de entrada, e necessario fornecer tambem o Servidor e Diretorio*/
int remove_data(TSTAMP_T idTx,LOCAL_T *local,TSTAMP_T tstamp,KEY_T key);

/*********************************************************
DEFINICAO FUNCOES QUE SÃO INDEPENDENTES DE INTERFACE
**********************************************************/

/*prototipo int find_slot_free(unsigned char**,int,int,int*)
 * descricao: busca um slot livre no bucket
 * parametros: p_buffer ->ponteiro para a posicao inicial
 * 												do mapa de bits no header
 *             numKeys -> qtd max de chaves no bucket, para limitar a busca no mapa de bits
 * 						 len_value -> length no value necessário para verificar
 * 													se o tamanho do valor e compativel com o slot
 * 						 offset -> retorna o offset para insercao do valor
 * retorno: a posicao do slot no mapa de bits*/
int find_slot_free(unsigned char **buffer,int numKeys,int len_value,int *offset);

/*prototipo int find_slot_key(unsigned char**,int,KEY_T)
 * descricao: busca a chave passada por parametro no slots
 * parametros: p_buffer ->ponteiro para a posicao inicial
 * 												do mapa de bits no header
 *             numKeys -> qtd max de chaves no bucket, para limitar a busca no mapa de bits
 * 						 key -> chave requisitada
 * retorno: a posicao do slot no mapa de bits*/
int find_slot_key(unsigned char **buffer,int numKeys,KEY_T key);

/*prototipo int get_len_slot(unsigned char*)
 * descricao: recupera o valor do length no slot
 * parametros: src ->ponteiro para a posicao do length no slot
 * retorno: um inteiro correspondente ao length*/
unsigned int get_len_slot(unsigned char *src);

/*prototipo int get_offset_slot(unsigned char*)
 * descricao: recupera o valor do offset no slot
 * parametros: src ->ponteiro para a posicao do offset no slot
 * retorno: um inteiro correspondente ao offset*/
unsigned int get_offset_slot(unsigned char *src);

/*prototipo KEY_T get_key_slot(unsigned char*)
 * descricao: recupera o valor da chave no slot
 * parametros: src ->ponteiro para a posicao da chave no slot
 * retorno: um inteiro correspondente a chave*/
KEY_T get_key_slot(unsigned char *src);

int get_numkeys_bucket(BUCKET_T *bucket);

/*prototipo int write_pair(BUCKET_T,KEY_T,char*)
 * descricao: busca um slot livre no bucket
 * parametros: buffer ->buffer que sera modificado
 *             numKeys -> qtd max de chaves no bucket, para limitar a busca no mapa de bits
 * 						 key -> chave que sera escrita
 * 						 value -> valor que sera escrito
 * retorno: inteiro indicativo de sucesso ou falha da operacao*/
//int write_pair(BUCKET_T *buffer,KEY_T key,char *value);

int persist_bucket(LOCAL_T *local,BUCKET_T *buffer,TSTAMP_T tstamp,TSTAMP_T version,size_t len_buffer);

/*prototipo int read_bucket(LOCAL_T**,TSTAMP_T,BUCKET_T**)
 * descricao: faz a leitura do bucket SO, se SE <> CURRENT_SERVER faz o request_bucket, senão
              solicita no s. armazenamento
 * parametros: local -> local do bucket
 *             tstamp -> timestamp de inicio da transacao para o SO
 *             data -> ponteiro para a variavel que recebe o bucket
 * retorno: situacao da operação*/
int read_bucket(LOCAL_T* local,TSTAMP_T tstamp, BUCKET_T* data);

/*prototipo: void send_bucket(REQBKET_T**,TSTAMP_T,BUCKET_T**)
 * descricao: função responsável por atender as solicitações de buckets vindas dos SE
 * parametros: char* frame frame contendo bucket requisitado
               char **data ponteiro contendo o bucket retornado*/
int send_bucket(LOCAL_T *local,TSTAMP_T tstamp,BUCKET_T *data);

/*prototipo void set_offset_slot(unsigned char**,int)
 * descricao: grava o valor do offset no slot
 * parametros: src ->ponteiro para a posicao do offset no slot
 * 						 offset ->valor que sera gravado*/
void set_offset_slot(unsigned char **src,unsigned int offset);

/*prototipo void set_len_slot(unsigned char**,int)
 * descricao: grava o valor do length no slot
 * parametros: src ->ponteiro para a posicao do length no slot
 * 						 length ->valor que sera gravado*/
void set_len_slot(unsigned char **src,unsigned int length);

/*prototipo void set_key_slot(unsigned char**,KEY_T)
 * descricao: grava o valor da chave no slot
 * parametros: src ->ponteiro para a posicao da chave no slot
 * 						 key ->chave que sera gravado*/
void set_key_slot(unsigned char **src,KEY_T key);

/*prototipo void write_slot(unsigned char**,unsigned int,unsigned int,KEY_T)
 * descricao: atualiza o slot no header
 * parametros: buffer ->ponteiro para a posicao inicial do slot no buffer
 * 						 offset -> offset que sera gravado
 * 						 length -> length que sera gravado
 * 						 key -> valor da chave que sera gravada
 * retorno: void*/
void write_slot(unsigned char **buffer,unsigned int slot_pos, unsigned int offset,unsigned int length,KEY_T key);

#endif
