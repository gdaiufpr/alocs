#ifndef UPD_HMAP_H
#define UPD_HMAP_H

#include "alocs_conf.h"
#include "hashmap.h"

typedef struct UPD_HMAP_S UPD_HMAP_T;
typedef struct ITENS_UPD_S ITENS_UPD_T;

struct ITENS_UPD_S{
  LOCAL_T local; //localização, do Bucket que foi alterado, no Servidor de Origem
  TSTAMP_T version;  //versão do Bucket no Servidor de Origem
  void *data; //ponteiro para o conteudo atualizado cache/fila
  struct ITENS_UPD_S *next;
};

struct UPD_HMAP_S{
  const char *source_server;
  int idTx;
  //int items_number;
  ITENS_UPD_T *items;
  int limit;
  int (*add)(UPD_HMAP_T **map,char *source_server,TSTAMP_T idTx,LINE_T *line);
  UPD_HMAP_T* (*get)(const UPD_HMAP_T *this,const char* source_server);
  ITENS_UPD_T* (*get_item)(const UPD_HMAP_T *this,LINE_T *line);
  int (*data_cmp)(const void *lhs,const void *rhs);
  void (*destroy)(UPD_HMAP_T **this);
};

extern void *new_map(MAP_TYPE_T map_type,int nbr_items);

#endif
