#include "alocs_conf.h"
#include "math.h"
#include "ccontrol_types.h"

#ifndef TXLIST_H
#define TXLIST_H


#define HTSIZE 1000

#define AVALUE ((sqrt(5) - 1) / 2)
#define HASH_TXLIST(k) ( HTSIZE * fmod((k * AVALUE),1) )

/*
 * tipos de dados da tabela hash
 */

typedef struct TXLIST_S TXLIST_T;
struct TXLIST_S{
  TSTAMP_T key;
  INFOTX_T *info_tx;
  struct TXLIST_S *next;
  void (*destroy)(TXLIST_T **this);
  INFOTX_T* (*get)(TXLIST_T *this,TSTAMP_T key);
  int (*put)(TXLIST_T *this,INFOTX_T **info_tx);
  int (*remove)(TXLIST_T *this,TSTAMP_T key);
};

 /*prototipo: void new_txlist(TXLIST_T **this)
  * descricao: cria uma nova lista de transações
  * parametros:*/
void new_txlist(TXLIST_T **this);

TXLIST_T *TXLIST;

#endif
