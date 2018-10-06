#include "util.h"

#ifndef ALOCS_CONF_H
#define ALOCS_CONF_H

//delimitadores dos ids
#define SRVNAME_SIZE   10
#define DIRNAME_SIZE   10
#define IDBUCKET_SIZE  10
#define LOCAL_SIZE     SRVNAME_SIZE + DIRNAME_SIZE + IDBUCKET_SIZE

//arquivo de configuracoes
#define CLIMIT_SLOT_SIZE 5
#define BLIMIT_SLOT_SIZE 5
#define CSERVER_SLOT_SIZE 10

//nomes do diretorio e arq. de conf.
#define DIR_CONF "SYSALOCS"
#define FILE_CONF "ALOCSCONF"

//definição do tamanho do timestamp no alocs
#define TSTAMP_SIZE 10

//qtd. total end points (servidores envolvidos)
#define SERVER_NUMBER 4

typedef enum TAGREG_E TAGREG_T;

//define o tipo TSTAMP_T referente aos timestamps utilizados no alocs
typedef uint64_t TSTAMP_T;

//define o tipo LOCALITY_T referente a localização do Bucket
typedef struct LOCAL_S{
  char key_ht[LOCAL_SIZE+1];
  char srv_name[SRVNAME_SIZE+1];
  char dir_name[DIRNAME_SIZE+1];
  char id_bucket[IDBUCKET_SIZE+1];
}LOCAL_T;

enum TAGREG_E{
  LINET_TAG = 0x0002bace,
  ITQT_TAG = 0x0002ace
};

//CURRENT SERVER
char CURRENT_SERVER[CSERVER_SLOT_SIZE];
//TAMANHO BUCKET
unsigned int LIMIT_SIZE_BUCKET;
//CAPACIDADE CACHE
unsigned int CACHE_LIMIT;


#endif
