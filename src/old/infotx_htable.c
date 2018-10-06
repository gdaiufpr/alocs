#include "include/infotx_htable.h"

/*prototipo: unsigned int get_hash(unsigned int key)
 * descricao: atribui um hash para a localizacao do bucket no cache
 * parametros: unsigned int key -> chave para o elemnto que esta sendo procurado*/
unsigned int get_hash(TSTAMP_T key){

  return HASH(key);
}

/*prototipo: create_infotx_htable
 * descricao: cria uma infotx-htable
 * parametros:*/
void create_infotx_ht(){

  int pos;

  //inicializa o indice
  INDEX = (INDEX_T *) xmalloc(sizeof(INDEX_T) * HTSIZE);

  //inicializacao da tabela hash
  for(pos = 0;pos < HTSIZE;pos++)
    (INDEX+pos)->node = NULL;

}

/*prototipo: NINDEX_T *search_infotx(TSTAMP_T)
 * descricao: localiza um elemento na htable
 * parametros: unsigned int key-> chave para o elemento que esta sendo procurado*/
NINDEX_T *search_infotx(TSTAMP_T key){

	INDEX_T *item;
  NINDEX_T *node;

  node = NULL;item = NULL;

	item = INDEX+get_hash(key);

  if(!item->node)
     return NULL;

  node = item->node;
  if(node->key == key) //se as chaves coincidirem
  	return node;
  else if(node->next){
    node = node->next;
    while((node != NULL)&&(node->key == key))
  		node = node->next;
  }

  return node;
}

/*prototipo: int insert_infotx(NINDEX_T)
 * descricao: insere um elemento na htable
 * parametros: NINDEX_T *new_node -> ponteiro para o elemento que sera inserido*/
int insert_infotx(NINDEX_T *new_node){

  INDEX_T *item;
  NINDEX_T *node;

  //busca a posicao na tabela hash
  item = INDEX+get_hash(new_node->key);

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

/*prototipo: int remove_infotx(TSTAMP_T)
 * descricao: remove um elemento na htable
 * parametros: unsigned int key -> chave para o elemnto que esta sendo procurado*/
int remove_infotx(TSTAMP_T key){

	INDEX_T *item;
  NINDEX_T *node;

  item = NULL;node = NULL;

  //busca a posicao na tabela hash
	item = INDEX+get_hash(key);

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
    node->key = node->next->key;
    node->infoTx = node->next->infoTx;
    node->next = node->next->next;
  }

  return 0;
}
