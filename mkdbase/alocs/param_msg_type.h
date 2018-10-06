#include <czmq.h>
#include "hashmap.h"

#ifndef PARAM_MSG_TYPE_H
#define PARAM_MSG_TYPE_H

typedef struct PARAM_S PARAM_T;
struct PARAM_S{
  int endp_nbr;
  char *end_points;
  zmsg_t *msg;
  size_t len_recv;
  CHAR_HMAP_T *recv;
  void (*destroy)(PARAM_T **this);
};


/*prototipo: void new_param(PARAM_T **this)
 * descricao: aloca memoria para uma nova estrutura param
 * parametros: PARAM_T **param ponteiro para o registro que sera inicializado*/
void new_param(PARAM_T **this);


#endif
