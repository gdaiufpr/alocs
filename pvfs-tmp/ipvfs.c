#include <stdio.h>
#include <stdlib.h>

/*
* Funcao que inicia o rados(), conecta no cluster
* arquivo de configuracao: /etc/ceph/ceph.conf
*/
int init_rados() {
}

/*
* Funcao que termina a conexao com o rados
* 
*/
int fin_rados(){
}

/**********************************
DEFINICAO OPERACOES INTERFACE S.A.
**********************************/
 
/*assinatura: int create_bucket(char *srvName,char *dirName,char *idBucket,unsigned int maxKeys)
 *objetivo: Cria um Bucket em Diretorio especificado nos parametros de entrada, em conjunto com o
 *					 identificador do Bucket, e Servidor.*/
/*
	*header definition
	*|----------|----------|----------|----------|----------|
	 |qtdChaves | bitmap   | OFFSET#1 | LENGTH#1 | KEY#1    |  
	 |----------|----------|----------|----------|----------|
	 |OFFSET#2  | LENGTH#2 | KEY#2    |   ...    | OFFSET#N |
	 |----------|----------|----------|----------|----------|
	 | LENGTH#N | KEY#N    | VALUE#1  ...  VALUE#N          |
	 |----------|----------|--------------------------------|
	*
	*max_keys = inteiro
	*bitmap = variavel
	*key (char(10)) conteudo da chave
	*offset (int) = localizacao dentro do bucket do value (deslocamento em relacao ao inicio do arquivo)
	*length = int tamanho de value
	*value (variavel) = valor do par chave-valor
	*
	*slot (key+offset+length)
*/
int ss_create_bucket(char *srvName,char *dirName,char *idBucket,unsigned int maxKeys) {
}

/*assinatura: int drop_bucket(char *idBucket,char *dirName,char *srvrName)
 *objetivo: Remove um Bucket, do Servidor e Diretório especificados por
 *parametros em conjunto com o identificador do Bucket*/
int ss_drop_bucket(char *idBucket,char *dirName,char *srvName) {
}

/*assinatura: int getBucket(char *srvName,char *dirName,char *idBucket)
 *objetivo: Retorna um Bucket, de um Diretorio e Servidor especificados nos parametros de entrada*/
//int ss_get_bucket(char *srvName,char *dirName,char *idBucket, BUCKET_T *buff_bucket){
//}

/*assinatura: int create_dir(char *dirName,char *srvName)
 *objetivo: Cria um Diretorio em Servidor especificado por parametro.*/
int ss_create_dir(char *dirName,char *srvName){
	system("/opt/orangefs/bin/pvfs2-mkdir /mnt/orangefs/srvName");
	system("/opt/orangefs/bin/pvfs2-mkdir /mnt/orangefs/srvName/dirName");
	return 1;
}

/*assinatura: int copy_dir(char *dirName,char *srvName1,char *srvName2)
 *objetivo: Copia um Diretorio de um Servidor para outro Servidor, ambos especificados por parametros.*/
int ss_copy_dir(char *dirName,char *srvName1,char *srvName2){
}

/*assinatura: int drop_dir(char *dirName,char *srvName)
 *objetivo: Remove um Diretorio de um Servidor, ambos especificados por parametros.*/
int ss_drop_dir(char *dirName,char *srvName){
	//system("/opt/orangefs/bin/pvfs2-rm -rf /mnt/orangefs/srvName/dirName");
	system("/opt/orangefs/bin/pvfs2-rm -rf /mnt/orangefs/srvName");
	return 1;
}

/*assinatura: int is_Empty(char *idBucket,char *dirName,char *srvName)
 *objetivo: Verifica se um Bucket, especificado por parametro, esta vazio, são indicados tambem o Diretorio e Servidor
 *TODO: pensar como fazer*/
int ss_is_empty_bucket(char *idBucket,char *dirName,char *srvName){
}

/*assinatura: int is_Empty(char *dirName,char *srvName)
 *objetivo: Verifica se um Diretório, especificado por parametro, está vazio, deve ser indicado tambem o Servidor
 *TODO: pensar como fazer*/
int ss_is_empty_dir(char *dirName,char *srvName){
}

/*assinatura: int put_pair(char *srvName,char *dirName,char *idBucket,KEY_T key,char *value)
 *objetivo: adicionar um par chave-valor no bucket passado por parametro*/
//int ss_put_pair(char *srvName,char *dirName,char *idBucket,KEY_T key,char *value){
//} 

/*assinatura: int rem_pair(char *srvName,char *dirName,char *idBucket,KEY_T key)
 *objetivo: Remove um par chave-valor do Bucket correspondente ao identificador passado como parametro
 *de entrada, e necessario fornecer tambem o Servidor e Diretorio*/
//int ss_remove_pair(char *srvName,char *dirName,char *idBucket,KEY_T key) {
//}

int main () {
	ss_drop_dir("Ruanito", "Diego");
}