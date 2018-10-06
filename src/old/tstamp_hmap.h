#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include "util.h"
#include "alocs_conf.h"

#ifndef TSTAMP_HMAP_H
#define TSTAMP_HMAP_H

typedef struct TSTAMP_HMAP_S TSTAMP_HMAP_T;
struct TSTAMP_HMAP_S{
    const char key[SRVNAME_SIZE];
    TSTAMP_T tstamp;
    int limit;
    int (*add_item)(TSTAMP_HMAP_T *this,const char *key, int value);
    TSTAMP_T (*get_item)(TSTAMP_HMAP_T *this,const char *key);
    int (*data_cmp)(const void *lhs,const void *rhs);
};

/*prototipo _add_item(TSTAMP_HMAP_T*,const char*,int)
 * descricao: adiciona um elemento ao hashmap
 * parametros: TSTAMP_HMAP_T *this mapa com os elementos
               const char *key chave que identifica o elemento no mapa
               int value valor correspondente a chave
 * retorno: um inteiro indicativo de falha ou sucesso*/
int _add_item(TSTAMP_HMAP_T *this,const char *key, int value);

/*prototipo void create_map(TSTAMP_HMAP_T**,int)
 * descricao: cria um mapa
 * parametros: TSTAMP_HMAP_T *map ponteiro para mapa que sera criado
               size_t size CAPACIDADE de armazenamento do mapa
 * retorno: mapa criado*/
void new_tstamp_map(TSTAMP_HMAP_T **map,int nbr_items);

/*prototipo int data_cmp(void const*,void const*)
 * descricao: funcao utilizada para comparar elementos na busca binaria
 * parametros: void const *lhs ponteiro para o elemento da esquerda
               void const *rhs ponteiro para o elemento da direita
 * retorno: um inteiro indicativo de falha ou sucesso*/
int _data_cmp(void const *lhs, void const *rhs);

/*prototipo char* _get_item(TSTAMP_HMAP_T*,const char*)
 * descricao: funcao utilizada para obter um elemento do mapa
 * parametros: TSTAMP_HMAP_T *this ponteiro para o mapa
               const char *key chave do elemento que esta sendo procurado
 * retorno: um ponteiro para o elemento encontrado */
TSTAMP_T _get_item(TSTAMP_HMAP_T *this,const char *key);

/*
    EXEMPLO UTILIZACAO

    data_t *hmap;
    int error;
    int limit = 4;
    data_t sKey;
    const data_t *res;

    error = create_map(&hmap,(sizeof(data_t) * limit));

    error = add_item_int(hmap,"SERVIDOR1", 10,limit);
    printf("key:%s value:%d\n",hmap->key,hmap->value);
    error = add_item_int(hmap,"SERVIDOR2", 20,limit);
    printf("key:%s value:%d\n",(hmap+1)->key,(hmap+1)->value);
    error = add_item_int(hmap,"SERVIDOR3", 30,limit);
    printf("key:%s value:%d\n",(hmap+2)->key,(hmap+2)->value);
    error = add_item_int(hmap,"SERVIDOR4", 40,limit);
    printf("key:%s value:%d\n",(hmap+3)->key,(hmap+3)->value);
    error = add_item_int(hmap,"SERVIDOR5", 50,limit);

    printf("buscar SERVIDOR4\n");

    sKey.key = "SERVIDOR4";
    res = get_item_char(&sKey,hmap,limit);

    if(res != NULL)
      printf("key:%s value:%d\n",res->key,res->value);
    else
      printf("item nao encontrado\n");

    free(hmap);
*/

#endif
