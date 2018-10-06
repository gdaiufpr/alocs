#include "cache_types.h"

#ifndef CACHE_HTABLE_H
#define CACHE_HTABLE_H

#define CONST1 1
#define CONST2 2
#define HASH2(k) (int)( 1 + fmod(k,(HTSIZE-1)) )
#define HASH(k,i) (int)( fmod(HASH2(k) + (CONST1 * i) + (CONST2 * pow(i,2)), HTSIZE) )

unsigned int HTSIZE;

/*prototipo: void create_htable()
 * descricao: cria o cache na memoria e inicializa o objeto CACHE
 * parametros:
   retorno: ponteiro para o slot encontrado  */
void create_htable();

//tabela hash para localizacao dos buckets no cache
CACHEHT_T *CACHEHT;

#endif
