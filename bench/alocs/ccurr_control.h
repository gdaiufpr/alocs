#include "alocs_conf.h"
#include "ccontrol_types.h"
#include "msg_service_req.h"
#include "up_queue.h"
#include "tx_list.h"

#ifndef CCURR_CONTROL_H
#define CCURR_CONTROL_H



/*prototipo: initTxControl()
 *descricao: iniciliaza o controle de transações */
void init_TxControl();

/*prototipo: TSTAMP_T begin_tx
 *descricao: inicia uma nova transação*/
TSTAMP_T begin_tx();

/*prototipo: void commit_tx(TSTAMP_T)
 *descricao: commita uma transação*/
int commit_tx(TSTAMP_T idTx);

/*prototipo: int get_global_clock(TSTAMP_HMAP_T**)
 *descricao: obtem o relogio logico global para a transacao
 paramentros: TSTAMP_HMAP_T **gClock -> ponteiro para o atributo do relogio em infoTx
 retorno: relogio global instanciado em gClock*/
int get_global_clock(TSTAMP_HMAP_T **gClock);

/*prototipo: int addInfoTx(INFOTX_T**)
 *descricao: adiciona infoTx na htable*/
int add_InfoTx(INFOTX_T **infoTx);

/*prototipo: void set_log_clock()
 *descricao: incrementa relógio lógico local
 paramentros:
 retorno: */
TSTAMP_T set_logical_clock();

int abort_tx(TSTAMP_T idTx,char *exec_server,ITENS_UPD_T *items);

int end_commit(TSTAMP_T idTx,const char *source_server);

/*prototipo: int validate_updates(TSTAMP_T,char*,ITENS_UPD_S*)
 * descricao: faz a validação das atualizações ocorridas em idTx
 * parametros: TSTAMP_T idTx id da transação que esta sendo validada
               char *source_server servidor de origem do buckets que foram atualizados
               ITENS_UPD_T *items vetor com os buckets atualizados
   retorno:situacao da operação             */
VALID_STATUS_T validate_updates(TSTAMP_T idTx,const char *source_server,ITENS_UPD_T *items);

/*prototipo: int register_updates(TSTAMP_T idTx,char *exec_server,ITENS_UPD_T *items)
 * descricao: faz o registro das atualizações que foram validadas
 * parametros: TSTAMP_T idTx id da transação que esta sendo validada
               char *exec_server id do servidor executor
               ITENS_UPD_T *items vetor com as atualizacoes
   retorno: VALID_STATUS_T situcao da validação             */
int register_updates(TSTAMP_T idTx,char *exec_server,ITENS_UPD_T *items);

#endif
