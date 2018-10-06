#include "include/cache_htable.h"

#define GET_HTSIZE() (ceil(CACHE_LIMIT/2))

/*prototipo: unsigned int get_hash(char* str)
 * descricao: atribui um hash para a localizacao do bucket no cache
 * parametros: str ->   idBucket do Bucket que esta no cache*/
unsigned int get_hash(char* str){

  int i;
  unsigned int number,h;

  number = h = 0;

  for(i = 0;i < strlen(str);i++)
     number += *(str+i);

  h = HASH(number);

  return h;
}

// A utility function to create an empty Hash of given capacity
void create_htable(){

  int pos;

  HTSIZE = GET_HTSIZE();
  //inicializa o indice
  CACHEHT = (CACHEHT_T *) xmalloc(sizeof(CACHEHT_T) * HTSIZE);

  //inicializacao da tabela hash
  for(pos = 0;pos < HTSIZE;pos++)
    (CACHEHT+pos)->node = NULL;

}

NODECHT_T *search_node_ht(char *key){

	CACHEHT_T *item;
  NODECHT_T *node;

  node = NULL;item = NULL;

	item = CACHEHT+get_hash(key);
  if(!item->node)
     return NULL;

  node = item->node;
  if(strcmp(node->key,key) == 0) //se as chaves coincidirem
  	return node;
  else if(node->next){
    node = node->next;
    while((node != NULL)&&(strcmp(node->key,key) != 0))
  		node = node->next;
  }

  return node;

}
/*prototipo: int insert_node_ht(char*,HEAPLRU_T**)
 * descricao: insere um item de cache em cacheht
 * parametros: key ->  idBucket do Bucket que esta sendo inserido no cache
               HEAPLRU_T** it_heap ponteiro para o item de cache que esta sendo inserido
   retorno: situação da operação             */
int insert_node_ht(char* key,HEAPLRU_T** it_cache){

  CACHEHT_T *item;
  NODECHT_T *node,*new_node;

  new_node = (NODECHT_T *) xmalloc(sizeof(NODECHT_T));

  strcpy(new_node->key,key);
  new_node->it_heap = *it_cache;
  new_node->next = NULL;

  //busca a posicao na tabela hash
  item = CACHEHT+get_hash(new_node->key);

  if(!item)  //por alguma razao nao encontrar a tab hash
    return 1;

  if(!item->node) //posicao livre no hash
    item->node = new_node;
  else{
    /*este loop sera utilizado em caso de colisao do hash
      percorre a lista encadeada ate encontrar o final da lista*/
    node = item->node;
    while((node->next != NULL))
      node = node->next;

    node->next = new_node;
  }

  return 0;
}

//verificar a necessidade desta funcao para a impl. no alocs
int remove_node_ht(char *key){

	CACHEHT_T *item;
  NODECHT_T *node;

  item = NULL;node = NULL;

  //busca a posicao na tabela hash
	item = CACHEHT+get_hash(key);

	if(!item)
	  return 1;

  node = item->node;
  if(!node)
    return 1;

  if(!node->next){  //se a lista escandeada tiver apenas um elemento
    free(node);
    item->node = NULL;
  }else{
    //se a lista escandeada tiver mais de um elemento
    strcpy(node->key,node->next->key);
    node->it_heap = node->next->it_heap;
    node->next = node->next->next;
  }

  return 0;

}
