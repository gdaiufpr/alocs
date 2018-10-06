#include "alocs_conf.h"
#include "cache_htable.h"
#include "storage_types.h"
#include "lock_service.h"
#include "up_queue.h"
#include "ccontrol_types.h"

#ifndef CACHE_H
#define CACHE_H


sem_t lock_meta,lock_line;

//linhas do cache
LINE_T *LINES;

/*********************************************************
DEFINICAO FUNCOES DO CACHE
**********************************************************/
/*prototipo int init_cache()
 * descricao: inicializa o cache no ALOCS, esta funcao e chamada na funcao init no common.c
 * parametros:
 * retorno: um inteiro indicativo de falha ou sucesso*/
int init_cache();

/*prototipo: int find_dirty_buffers()
 * descricao: percorre o buffer pool em busca de buffers alterados (sujos)
 * 						os buffer sujos sao apontados na lista DIRTY_BUFFERS que e acessada
 * 						pela interface do sa
 * parametros:
 * retorno: qtd de buffers alterados */
//int find_dirty_buffers();

#endif
