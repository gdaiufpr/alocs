#include "storage_types.h"
#include "hashmap.h"
#include "valid_hmap.h"
#include "upd_hmap.h"

#ifndef CCONTROL_TYPES_H
#define CCONTROL_TYPES_H

typedef enum VALID_STATUS_E VALID_STATUS_T;
enum VALID_STATUS_E{
  UPD_ACCEPT = 0,
  UPD_DENIAL = 1,
  VALID_ERROR = 2
};

typedef struct INFOTX_S{
  TSTAMP_T idTx; //identificador unico
  char id_server[SRVNAME_SIZE]; //identificador do Servidor Executor
  TSTAMP_HMAP_T *g_clock;  //relogio logico global para a transação
  char* bck_list; //buckets acessados na transacao
  UPD_HMAP_T *updates;
}INFOTX_T;

/*prototipo: TSTAMP_T get_logical_clock()
 *descricao: retorna o relógio lógico do servidor
 paramentros:
 retorno: TSTAMP_T relógio lógico*/
TSTAMP_T get_logical_clock();

/*prototipo: TSTAMP_T get_init_tstamp(TSTAMP_T )
  descricao: obtém o timestamp de inicio do SO para a transação
  paramentros: TSTAMP_T idTx -> id da transação fornecido pela app
 retorno: TSTAMP_T tstamp */
TSTAMP_T get_init_tstamp(TSTAMP_T idTx,char* srv_name);

INFOTX_T* get_infotx(TSTAMP_T idTx);

#endif
