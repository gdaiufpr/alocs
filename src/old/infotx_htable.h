#include "ccontrol_types.h"

#ifndef INFOTX_HTABLE_H
#define INFOTX_HTABLE_H

#define HTSIZE 1000

#define AVALUE ((sqrt(5) - 1) / 2)
#define HASH(k) ( HTSIZE * fmod((k * AVALUE),1) )

/*
 * tipos de dados da tabela hash
 */

typedef struct NINDEX_S{
   TSTAMP_T key;
   INFO_T *infoTx;
   struct NINDEX_S *next;
}NINDEX_T;

typedef struct INDEX_S{
  NINDEX_T *node;
}INDEX_T;

/*prototipo: unsigned int get_hash(TSTAMP_T key)
 * descricao: atribui um hash para a localizacao do bucket no cache
 * parametros: unsigned int key -> chave para o elemento que esta sendo procurado*/
unsigned int get_hash(TSTAMP_T key);

/*prototipo: create_infotx_htable
 * descricao: cria uma infotx-htable
 * parametros:*/
void create_infotx_ht();

/*prototipo: NINDEX_T *search_infotx(TSTAMP_T)
 * descricao: localiza um elemento na htable
 * parametros: unsigned int key-> chave para o elemento que esta sendo procurado*/
NINDEX_T *search_infotx(TSTAMP_T key);

/*prototipo: int insert_infotx(NINDEX_T)
 * descricao: insere um elemento na htable
 * parametros: NINDEX_T *new_node -> ponteiro para o elemento que sera inserido*/
int insert_infotx(NINDEX_T *new_node);

/*prototipo: int remove_infotx(TSTAMP_T key)
 * descricao: remove um elemento na htable
 * parametros: unsigned int key -> chave para o elemnto que esta sendo procurado*/
int remove_infotx(TSTAMP_T key);

//tabela hash para localizacao dos registros INFOTX
INDEX_T *INDEX;

#endif
