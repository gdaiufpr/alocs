#ifndef VALID_HMAP_H
#define VALID_HMAP_H

#include "alocs_conf.h"
#include "hashmap.h"
#include "ccontrol_types.h"

typedef struct VALID_HMAP_S VALID_HMAP_T;

struct VALID_HMAP_S{
  const char *source_server;
  VALID_STATUS_T valid;
  int limit;
  int (*add_item)(VALID_HMAP_T *this,const char *source_server,VALID_STATUS_T valid);
  VALID_HMAP_T* (*get_item)(const VALID_HMAP_T *this,const char *source_server);
  int (*data_cmp)(const void *lhs,const void *rhs);
  void (*destroy)(VALID_HMAP_T **this);
};

extern void *new_map(MAP_TYPE_T map_type,int nbr_items);

#endif
