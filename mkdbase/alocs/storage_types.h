#include "cache_types.h"

#ifndef STORAGE_TYPES_H
#define STORAGE_TYPES_H

#define BCKT_VERSION_SIZE 10
#define FNAME_SIZE IDBUCKET_SIZE + BCKT_VERSION_SIZE

/*
* constantes para manipulacao do bucket
*/
#define BYTES_LIMIT      4
#define LCKFLAG_OFFSET   0
#define MBITS_OFFSET    13
#define LOCK_FLAG_SIZE   1
#define SLOT_SIZE       18
#define OFF_SLOT_SIZE    4
#define LEN_SLOT_SIZE    4
#define KEY_SLOT_SIZE   10
#define TSTAMP_OFFSET    5
#define VERSION_OFFSET   9

/*tamanho do header é definido por
  LOCK_FLAG(1 BYTE) + QTDCHAVES(4 BYTES) + TSTAMP(4 BYTES) +  VERSION(4 BYTES) + BITMAP(K) + SLOTS(k * SLOT_SIZE*/
#define HEADER_SIZE(k) (LOCK_FLAG_SIZE + BYTES_LIMIT*3 + k + (k * SLOT_SIZE) + 1)

//define o tipo KEY_T referente a chave
typedef uint64_t KEY_T;

//define o tipo BUCKET_T referente ao bucket
typedef unsigned char *BUCKET_T;

//define o tipo PAIR_T referente ao par chave valor
typedef struct PAIR_S{
  KEY_T key;
  char *value;
}PAIR_T;

typedef struct REQBKET_S{
  LOCAL_T local;
  TSTAMP_T tstamp;
}REQBKET_T;

/*prototipo void format_fname(char*,size_t,char*,TSTAMP_T)
 * descricao: formata o idbucket com o tstamp para gerar a versao do bucket
 * parametros: char *id_bucket_f string resultante da formatacao
 *             char *id_bucket id_bucket sem versao
 *             char *version  version do tipo TSTAMP_T*/
void format_fname(char *obj_id,char *id_bucket,TSTAMP_T version);

extern int find_conflict_version(LOCAL_T *local,TSTAMP_T version);

/*prototipo unsigned int get_version_bucket(BUCKET_T *bucket)
 * descricao: extrai a versao do bucket
 * parametros: BUCKET_T* ponteiro para o bucket que sera criado*/
unsigned int get_version_bucket(BUCKET_T *bucket);

/*prototipo unsigned int get_version_bucket(BUCKET_T *bucket)
 * descricao: extrai o tstamp de commit do bucket
 * parametros: BUCKET_T* ponteiro para o bucket que sera criado*/
unsigned int get_tstamp_bucket(BUCKET_T *bucket);

/*prototipo void new_bucket(BUCKET_T*)
 * descricao: aloca espaco na memoria para um novo bucket
 * parametros: BUCKET_T* ponteiro para o bucket que sera criado*/
void new_bucket(BUCKET_T* bucket);


#endif
