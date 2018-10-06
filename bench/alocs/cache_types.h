#include "alocs_conf.h"
#include <math.h>

#ifndef CACHE_TYPES_H
#define CACHE_TYPES_H


/*typedef struct DIRTYLINES_S{
    LOCAL_T local;
    unsigned char *data;
    struct DIRTYLINES_S *next;
}DIRTYLINES_T;*/

//tipo de dados do heap para o lru
/*typedef struct HEAPLRU_S{
  int indx;
  char key[IDBUCKET_SIZE+1];
  unsigned int tstamp;
  LINE_T *line;
}HEAPLRU_T;

//tipo de dados da tabela hash
typedef struct NODECHT_S{
  char key[IDBUCKET_SIZE+1];
  HEAPLRU_T *it_heap;
  struct NODECHT_S *next;
}NODECHT_T;*/

typedef enum TYPE_OPER_TX_E TYPE_OPER_TX_T;
enum TYPE_OPER_TX_E{
  READ_WRITE = 0,
  READ_ONLY = 1
};

typedef enum CACHE_GET_RET_E CACHE_GET_RET_T;
enum CACHE_GET_RET_E{
  CACHE_HIT     = 10,
  CACHE_BLOQUED = 20,
  CACHE_MISS    = 30,
  CACHE_ERROR   = 0
};

typedef enum CACHE_LCKTYPE_E CACHE_LCKTYPE_T;
enum CACHE_LCKTYPE_E{
  LOCK_META = 0,
  LOCK_LINE = 1
};

//estrutura de dados para as linhas de cache
typedef struct LINE_S{
  TAGREG_T tag;
  unsigned int id_line;
  LOCAL_T local; //posteriormente mudar para o tipo registro LOCAL_T
  TSTAMP_T version;
  TSTAMP_T tstamp;
  int dirty;
  int read_only;
  TSTAMP_T writer;
  int locked;
  unsigned char *data;
}LINE_T;

//lista de linhas pre-alocadas
/*typedef struct LINELIST_S{
  LINE_T line;
  struct LRULIST_S *prev;
  struct LRULIST_S *next;
};*/

//estrutura para o LRU
typedef struct LRULIST_S{
  LINE_T *line;
  struct LRULIST_S *prev;
  struct LRULIST_S *next;
}LRULIST_T;

typedef struct CACHE_S CACHE_T;
struct CACHE_S{
  LRULIST_T *head;
  LRULIST_T *tail;
  int locked;
  void (*destroy)(CACHE_T **this);
  LINE_T* (*is_line)(void *pointer);
  int (*get)(LINE_T **line,LOCAL_T *local,TSTAMP_T tstamp,int idTx,TYPE_OPER_TX_T type_oper);
  LINE_T* (*put)(CACHE_T *this,LOCAL_T *local,TSTAMP_T tstamp,unsigned char **data,int writer,TYPE_OPER_TX_T type_oper);
  int (*lock)(CACHE_T *this,CACHE_LCKTYPE_T lock_type,LINE_T *line);
  int (*unlock)(CACHE_T *this,CACHE_LCKTYPE_T lock_type,LINE_T *line);
  int (*remove)(CACHE_T *this,LINE_T **line);
  void (*set_dirty)(TSTAMP_T idTx,LINE_T **line,int dirty);
};

typedef struct CACHEHT_S CACHEHT_T;
struct CACHEHT_S{
  unsigned int key;
  LRULIST_T *it_cache;
  int (*get)(CACHEHT_T *this,LRULIST_T **it_cache,LOCAL_T *local,TSTAMP_T tstamp,int idTx,TYPE_OPER_TX_T type_oper);
  void (*destroy)(CACHEHT_T **this);
  int (*put)(CACHEHT_T *this,LOCAL_T *local,LRULIST_T **it_cache);
  int (*remove)(CACHEHT_T *this,LOCAL_T *local,unsigned int id_line);
};

//CACHE BASEADO EM LRU
CACHE_T *CACHE;

#endif
