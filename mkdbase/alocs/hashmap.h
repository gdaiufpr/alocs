#ifndef HASHMAP_H
#define HASHMAP_H

#include "alocs_conf.h"

typedef enum MAP_TYPE_E MAP_TYPE_T;
enum MAP_TYPE_E{
  CHAR_TYPE = 0,
  TSTAMP_TYPE = 1,
  INT_TYPE = 2,
  UPD_TYPE = 3,
  VALID_TYPE = 4
};

typedef struct CHAR_HMAP_S CHAR_HMAP_T;
typedef struct TSTAMP_HMAP_S TSTAMP_HMAP_T;
typedef struct INT_HMAP_S INT_HMAP_T;

struct TSTAMP_HMAP_S{
    const char *key;
    TSTAMP_T tstamp;
    int limit;
    int (*add_item)(TSTAMP_HMAP_T *this,const char *key,TSTAMP_T tstamp);
    TSTAMP_T (*get_item)(const TSTAMP_HMAP_T *this,const char* key);
    int (*data_cmp)(const void *lhs,const void *rhs);
    void (*destroy)(TSTAMP_HMAP_T **this);
};

struct CHAR_HMAP_S{
    const char *key;
    unsigned char *value;
    int limit;
    int (*add_item)(CHAR_HMAP_T *this,const char *key, char *value);
    char* (*get_item)(const CHAR_HMAP_T *this,const char* key);
    int (*data_cmp)(const void *lhs,const void *rhs);
    void (*destroy)(CHAR_HMAP_T **this);
};

struct INT_HMAP_S{
    const char *key;
    int value;
    int limit;
    int (*add_item)(INT_HMAP_T *this,const char *key, int value);
    int (*get_item)(const INT_HMAP_T *this,const char* key);
    int (*data_cmp)(const void *lhs,const void *rhs);
    void (*destroy)(INT_HMAP_T **this);
};

void *new_map(MAP_TYPE_T map_type,int nbr_items);

#endif
