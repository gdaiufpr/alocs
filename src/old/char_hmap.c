#include "include/char_hmap.h"

/*prototipo void new_char_map(CHAR_HMAP_T**,int)
 * descricao: cria um mapa
 * parametros: CHAR_HMAP_T *map ponteiro para mapa que sera criado
               int nbr_items CAPACIDADE de armazenamento do mapa
 * retorno: mapa criado*/
void new_char_map(CHAR_HMAP_T **map,int nbr_items){

  *map = (CHAR_HMAP_T *)xmalloc(sizeof(CHAR_HMAP_T) * nbr_items);

  (*map)->limit = nbr_items;
  (*map)->get_item = _get_item;
  (*map)->add_item = _add_item;
  (*map)->data_cmp = _data_cmp;
}

/*prototipo void destroy_char_map(CHAR_HMAP_T **map)
 * descricao: destroi um mapa
 * parametros: CHAR_HMAP_T *map ponteiro para mapa que sera criado
 * retorno: */
void destroy_char_map(CHAR_HMAP_T **map){

  int indx;
  int limit = *map->limit;

  for(indx = 0;indx < limit;indx++)
      free((*map+indx)->value);

  free(*map);
}

/*prototipo int _add_item(CHAR_HMAP_T*,const char*,int)
 * descricao: adiciona um elemento ao hashmap
 * parametros: CHAR_HMAP_T *this mapa que onde o elemento será adicionado
               const char *key chave que identifica o elemento no mapa
               int value valor correspondente a chave
 * retorno: um inteiro indicativo de falha ou sucesso*/
int _add_item(CHAR_HMAP_T *this,const char *key, int value){
  static int indx=0;

  if(indx < this->limit){
    (this+indx)->key = key;
    (this+indx)->value = strdup(value);

    indx++;
  }else{
     fprintf(stderr,"[add_item/char_hmap.c]Limite do array atingido!!\n");
     return 1;
  }
}

/*prototipo int _data_cmp(void const*,void const*)
 * descricao: funcao utilizada para comparar elementos na busca binaria
 * parametros: void const *lhs ponteiro para o elemento da esquerda
               void const *rhs ponteiro para o elemento da direita
 * retorno: um inteiro indicativo de falha ou sucesso*/
int _data_cmp(void const *lhs, void const *rhs){
  const CHAR_HMAP_T *l = lhs;
  const CHAR_HMAP_T *r = rhs;
  int res;

  res = strcmp(l->key,r->key);
  if(res < 0)
     return -1;
  else if(res > 0)
     return 1;

  return 0;
}

/*prototipo char* _get_item(CHAR_HMAP_T*,const char*)
 * descricao: funcao utilizada para obter um elemento do mapa
 * parametros: CHAR_HMAP_T *this ponteiro para o mapa
               const char *key chave do item que esta sendo procurado
 * retorno: valor correspondente a chave */
char* _get_item(CHAR_HMAP_T *this,const char *key){

  CHAR_HMAP_T *res;
  CHAR_HMAP_T sKey = {.key = key};
  const data_t *search = &sKey;

  res = bsearch(search,this,COUNT_ITMAP(sizeof(CHAR_HMAP_T),this->limit), SIZE_ITMAP(sizeof(CHAR_HMAP_T)),this->data_cmp);

  return res->value;
}
