#include <czmq.h>
#include "hashmap.h"
#include "param_msg_type.h"
#include "upd_hmap.h"

#ifndef MSG_SERVICE_REQ_H
#define MSG_SERVICE_REQ_H

CHAR_HMAP_T *ENDP_MAP;

/*prototipo: init_msgservice()
 * descricao: inicializa serviço de mensagens
 * parametros: */
int init_msgservice();

/*prototipo: send_req_abort(char* end_points,int endp_nbr,UPD_HMAP_T *updates,PARAM_T **param)
 * descricao: esta função permite que o Servidor Executor envie request_abort para os SO
 * parametros: char *end_points -> vetor contendo os end_points ,
               int endp_nbr -> qtd. de end points (servidores que receberam msg)
               UPD_HMAP_T *updates -> vetor com as atualizacoes que seram enviadas
               param_t **param  -> um ponteiro para estrutura que contera a resposta dos servidores*/
int send_req_abort(char* end_points,int endp_nbr,UPD_HMAP_T *updates,PARAM_T **param);

/*prototipo: send_req_endcommit(char* end_points,int endp_nbr,UPD_HMAP_T *updates,PARAM_T **param)
 * descricao: esta função permite que o Servidor Executor envie request_endcommit para os SO
 * parametros: char *end_points -> vetor contendo os end_points ,
               int endp_nbr -> qtd. de end points (servidores que receberam msg)
               UPD_HMAP_T *updates -> vetor com as atualizacoes que seram enviadas
               param_t **param  -> um ponteiro para estrutura que contera a resposta dos servidores*/
int send_req_endcommit(char* end_points,int endp_nbr,UPD_HMAP_T *updates,PARAM_T **param);

/*prototipo: int send_req_clock(char *end_points,int endp_nbr,PARAM_T **param)
 * descricao: esta função permite que o Servidor Executor envie msgs para os Servidores Origem
 * parametros: char *msg -> msg que sera enviada,
               int endp_nbr -> qtd. de end points (servidores que receberam msg)
               char *end_points -> vetor com servidores que receberam msg
               param_t **param  -> um ponteiro para estrutura que contera a responsta dos servidores*/
int send_req_clock(int endp_nbr,PARAM_T **param);

/*prototipo: send_req_bucket(char*,REQBKET_T*,param_t**)
 * descricao: esta função permite que o Servidor Executor envie msgs para os Servidores Origem
 * parametros: char srvName -> identificador do servidor Origem
               int endp_nbr -> qtd. de end points (servidores que receberão msg)
               LOCALITY_T local -> localidade do bucket requisitado
               PARAM_T **param  -> um ponteiro para estrutura que contera a resposta dos servidores*/
int send_req_bucket(char *srv_name,int endp_nbr,REQBKET_T* req_bucket,PARAM_T **param);

/*prototipo: send_req_register(char* end_points,int endp_nbr,UPD_HMAP_T *updates,PARAM_T **param)
 * descricao: esta função permite que o Servidor Executor envie request_validate para os SO
 * parametros: char *end_points -> vetor contendo os end_points ,
               int endp_nbr -> qtd. de end points (servidores que receberam msg)
               UPD_HMAP_T *updates -> vetor com as atualizacoes que seram enviadas
               param_t **param  -> um ponteiro para estrutura que contera a resposta dos servidores*/
int send_req_register(char* end_points,int endp_nbr,UPD_HMAP_T *updates,PARAM_T **param);

/*prototipo: int send_req_validate(char* end_points,int endp_nbr,UPD_HMAP_T *updates,param_t **param)
 * descricao: esta função permite que o Servidor Executor envie request_validate para os SO
 * parametros: char *end_points -> vetor contendo os end_points ,
               int endp_nbr -> qtd. de end points (servidores que receberam msg)
               UPD_HMAP_T *updates -> vetor com as atualizacoes que seram enviadas
               param_t **param  -> um ponteiro para estrutura que contera a resposta dos servidores*/
int send_req_validate(char* end_points,int endp_nbr,UPD_HMAP_T *updates,PARAM_T **param);

#endif
