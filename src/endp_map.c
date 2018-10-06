#include "include/endp_map.h"

#define GET_HTABLE_SIZE() (SERVER_NUMBER * 2)

/*prototipo: void destroy_htable()
 * descricao: desaloca os espacos de memoria utilizados por ENDMAP
 * parametros:
   retorno: ponteiro para o slot encontrado  */
void _destroy_endmap(ENDPMAP_T **this);

/*prototipo: int _search_end(ENDPMAP_T*,ENDPMAP_T**,TSTAMP_T,int,char*)
 * descricao: busca um bucket em ENDMAP, esta operacao e executada por CACHE->get
 * parametros: ENDPMAP_T *this -> ponteiro para ENDMAP
               ENDPMAP_T **slot -> ponteiro para o slot que sera retornado
               LOCAL_T *local -> localidade do bucket
               TSTAMP_T tstamp -> tstamp de inicio
               int idTx -> id da transacao que modificou a linha
   retorno: ponteiro para o slot encontrado  */
const char* _search_end(ENDPMAP_T *this,const char *id_server);

/*prototipo: int _insert_end(ENDPMAP_T*,LOCAL_T*,LRULIST_T**)
 * descricao: insere um item de cache em ENDMAP
 * parametros: ENDPMAP_T *this -> ponteiro para ENDMAP
               LOCAL_T *local ->  localidade do bucket a ser inserido
               HEAPLRU_T** it_heap ponteiro para o item de cache que esta sendo inserido
   retorno: situação da operação             */
int _insert_end(ENDPMAP_T *this,const char *id_server,char *end_point);

/*prototipo: int _remove_node(CENDPMAP_T*,LOCAL_T*,unsigned int)
 * descricao: insere um item de cache em ENDMAP
 * parametros: ENDPMAP_T *this -> ponteiro para ENDMAP
               LOCAL_T *local ->  localidade do bucket utilizada como chave
               unsigned int id_line -> id da linha de cache a ser removida
   retorno: situação da operação             */
//int _remove_node(ENDPMAP_T *this,LOCAL_T *local,unsigned int id_line);

/*prototipo: unsigned int conv_key(char* str)
 * descricao: converte a chave em numero
 * parametros: key -> localidade (servidor/diretorio/bucket) do Bucket que esta no cache*/
unsigned int conv_key(const char* key);

/*prototipo: void create_htable()
 * descricao: cria o cache na memoria e inicializa o objeto CACHE
 * parametros:
   retorno: ponteiro para o slot encontrado  */
void new_endmap(ENDPMAP_T **this){

  int pos,error;

  HTABLE_SIZE = GET_HTABLE_SIZE();

  //inicializa o indice
  *this = (ENDPMAP_T *) xmalloc(sizeof(ENDPMAP_T) * HTABLE_SIZE);

  //inicializacao da tabela hash
  for(pos = 0;pos < HTABLE_SIZE;pos++){
    (*this+pos)->key = 0;
    memset((*this+pos)->end_point,'\0',ENDPVAR_SIZE);

    (*this+pos)->get = _search_end;
    (*this+pos)->put = _insert_end;
    //(*this+pos)->remove = _remove_node;
    (*this+pos)->destroy = _destroy_endmap;
  }
}

/*prototipo: void destroy_htable()
 * descricao: desaloca os espacos de memoria utilizados por ENDMAP
 * parametros:
   retorno: ponteiro para o slot encontrado  */
void _destroy_endmap(ENDPMAP_T **this){

  int pos;

  free(*this);
}

/*prototipo: int _search_end(ENDPMAP_T*,ENDPMAP_T**,TSTAMP_T,int,char*)
 * descricao: busca um bucket em ENDMAP, esta operacao e executada por CACHE->get
 * parametros: ENDPMAP_T *this -> ponteiro para ENDMAP
               ENDPMAP_T **slot -> ponteiro para o slot que sera retornado
               LOCAL_T *local -> localidade do bucket
               TSTAMP_T tstamp -> tstamp de inicio
               int idTx -> id da transacao que modificou a linha
   retorno: ponteiro para o slot encontrado  */
const char* _search_end(ENDPMAP_T *this,const char *id_server){

  int i,find;
  unsigned int int_key;
  ENDPMAP_T *slot;

  slot = NULL;

  int_key = conv_key(id_server);

  i = 0;
  find = 0;
  do{
    slot = this+(HASHF(int_key,i++));
    if(slot){
      if( ( slot->key == int_key) )
        find = 1;
    }
  }while( !find && (i < HTABLE_SIZE) );

  return slot->end_point;

}

/*prototipo: int _insert_end(ENDPMAP_T*,LOCAL_T*,LRULIST_T**)
 * descricao: insere um item de cache em ENDMAP
 * parametros: ENDPMAP_T *this -> ponteiro para ENDMAP
               LOCAL_T *local ->  localidade do bucket a ser inserido
               HEAPLRU_T** it_heap ponteiro para o item de cache que esta sendo inserido
   retorno: situação da operação             */
int _insert_end(ENDPMAP_T *this,const char *id_server,char *end_point){

  int i;
  ENDPMAP_T *slot;
  unsigned int int_key;

  int_key = conv_key(id_server);

  i = 0;
  do{
   slot = this+HASHF(int_key,i++);
  }while( (slot->key > 0) && (i < HTABLE_SIZE) );

  slot->key = int_key;
  strcpy(slot->end_point,end_point);

  return 0;
}

/*prototipo: int _remove_node(CENDPMAP_T*,LOCAL_T*,unsigned int)
 * descricao: insere um item de cache em ENDMAP
 * parametros: ENDPMAP_T *this -> ponteiro para ENDMAP
               LOCAL_T *local ->  localidade do bucket utilizada como chave
               unsigned int id_line -> id da linha de cache a ser removida
   retorno: situação da operação             */
/*int _remove_node(ENDPMAP_T *this,LOCAL_T *local,unsigned int id_line){

	ENDPMAP_T *slot;
  LINE_T *line;
  int find,i;
  unsigned int int_key;

  int_key = conv_key(local->key_ht);

  i = find = 0;
  slot = NULL;
  do{
    slot = this+(HASHF(int_key,i++));
    line = slot->it_cache->line;

    if(line){
      if( (slot->key == int_key) && (line->id_line == id_line) )
        find = 1;
    }
  }while( !find && (i < HTABLE_SIZE) );

  fprintf(stderr, "[debug ENDMAP] encontrou na cache para remocao:%d\n",find );
  slot->key = 0;
  slot->it_cache = NULL;

  return 0;
}*/

/*prototipo: unsigned int conv_key(char* str)
 * descricao: converte a chave em numero
 * parametros: key -> localidade (servidor/diretorio/bucket) do Bucket que esta no cache*/
unsigned int conv_key(const char* key){

  int i;
  unsigned int number,h;

  number = h = 0;

  for(i = 0;i < strlen(key);i++)
     number += *(key+i);

  return number;
}
