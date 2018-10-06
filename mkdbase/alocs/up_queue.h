#include "alocs_conf.h"
#include "storage_types.h"
#include "lock_service.h"
#include "upd_hmap.h"

#ifndef UP_QUEUE_H
#define UP_QUEUE_H

//define a estrutura de dados para armazenar dados da fila
typedef struct ITQUEUE_S{
  TAGREG_T tag;
  TSTAMP_T idTx; //identificador da transação que modificou o bucket
  TSTAMP_T tstamp; //timestamp de commit
	LOCAL_T local;  //local onde o bucket esta alocado servidor/diretorio/bucket
  TSTAMP_T version; //versão do Bucket no SE
  char *id_server; //identificador do Servidor Executor
	BUCKET_T data; //bucket modificado
  struct ITQUEUE_S *prev;
  struct ITQUEUE_S *next;
}ITQUEUE_T;

typedef struct UPQUEUE_S UPQUEUE_T;
struct UPQUEUE_S{
  ITQUEUE_T *head;
  ITQUEUE_T *tail;
  int locked;
  void (*destroy)(UPQUEUE_T **this);
  int (*is_itqueue)(void *pointer);
  ITQUEUE_T* (*get)(UPQUEUE_T *this,char *id_bucket);
  ITQUEUE_T* (*put)(UPQUEUE_T *this,TSTAMP_T idTx,TSTAMP_T tstamp,LOCAL_T *local,TSTAMP_T version,char *exec_server,BUCKET_T *data);
  int (*lock)(UPQUEUE_T *this,const char *id_server);
  int (*unlock)(UPQUEUE_T *this,const char *id_server);
  int (*remove)(ITQUEUE_T **item);
};

sem_t lock_queue;

UPQUEUE_T *UPQUEUE;

/*prototipo: void new_upqueue(UPQUEUE_T **this)
 * descricao: inicializa uma nova fila de atualizacoes
 * parametros: UPQUEUE_T **this -> ponteiro para a fila
 */
void new_upqueue(UPQUEUE_T **this);

#endif
