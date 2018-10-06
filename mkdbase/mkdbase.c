#include <stdlib.h>
#include <stdio.h>
#include "alocs/libalocs.h"

#define SRVNAME_SIZE   10
#define DIRNAME_SIZE   10
#define IDBUCKET_SIZE  10
#define LOCAL_SIZE     SRVNAME_SIZE + DIRNAME_SIZE + IDBUCKET_SIZE

//#define CSERVER  "SRVPR"

#define VALUE_SIZE     50
#define ID_SIZE        50

#define BUCKET_NUMBER  25

#define IT_NUMBER       5

void app_create_server();
void app_create_dir();
void app_drop_dir();
void app_create_bucket();
void app_drop_bucket();
//void app_put_pair();
//void app_get_pair();
void app_remove_pair();

int ret_oper;
char id_bucket[IDBUCKET_SIZE],dir_name[DIRNAME_SIZE],srv_name[SRVNAME_SIZE];
char value[VALUE_SIZE];
uint64_t initKey,finKey,key;
PAIR_T pair;

char CSERVER[SRVNAME_SIZE];

void app_create_server(){
	printf("Create Server\n");

	if(strcmp(CSERVER,"SRVPR") == 0){
		ret_oper = create_server("SRVPR");
	}else if(strcmp(CSERVER,"SRVRS") == 0)
		ret_oper = create_server("SRVRS");
	else if(strcmp(CSERVER,"SRVSC") == 0)
		ret_oper = create_server("SRVSC");
	else if(strcmp(CSERVER,"SRVSP") == 0)
		ret_oper = create_server("SRVSP");

	if(ret_oper == 1)
		fprintf(stdout,"[app_create_dir/app_client.c] O Servidor não foi criado!\n");

}

void app_create_dir(){
	printf("Create Dir\n");

	if(strcmp(CSERVER,"SRVPR") == 0){
		ret_oper = create_dir("CURITIBA",CSERVER);
		//ret_oper = create_dir("PINHAIS",CSERVER);
	}else if(strcmp(CSERVER,"SRVRS") == 0){
		ret_oper = create_dir("PALEGRE",CSERVER);
		//ret_oper = create_dir("GRAMADO",CSERVER);
	}else if(strcmp(CSERVER,"SRVSC") == 0){
		ret_oper = create_dir("FNOPOLIS",CSERVER);
		//ret_oper = create_dir("CAMBORIU",CSERVER);
	}else if(strcmp(CSERVER,"SRVSP") == 0){
		ret_oper = create_dir("SPAULO",CSERVER);
		//ret_oper = create_dir("CAMPINAS",CSERVER);
	}

	if(ret_oper == 1)
		fprintf(stdout,"[app_create_dir/app_client.c] O Diretório não foi criado!\n");

}

void app_create_bucket(){

  int i,init_key,fin_key,pair_number;
  int buck_nbr;
  char dir_name[ID_SIZE];
  char id_bucket[ID_SIZE];

  //buck_nbr = 250;
	//buck_nbr = 15;
	pair_number = 99;

	if(strcmp(CSERVER,"SRVPR") == 0){
		init_key = 1;
		strcpy(dir_name,"CURITIBA");
		for(i = 1;i <= BUCKET_NUMBER;i++){
			fin_key = init_key+pair_number;
			snprintf(id_bucket,ID_SIZE,"BUCK%dCT",i);
			ret_oper = create_bucket(CSERVER,dir_name,id_bucket,init_key,fin_key);
			fprintf(stdout, "criou bucket %s no intervalo %d até %d\n",id_bucket,init_key,fin_key);
			init_key = fin_key +1;
    }
	}else if(strcmp(CSERVER,"SRVRS") == 0){
		//init_key = 25001; 250
		//init_key = 12501; 125
                //init_key = 5001; 50
		init_key = (BUCKET_NUMBER * 100) + 1;
		strcpy(dir_name,"PALEGRE");
		for(i = 1;i <= BUCKET_NUMBER;i++){
			fin_key = init_key+pair_number;
			snprintf(id_bucket,ID_SIZE,"BUCK%dPA",i);
			ret_oper = create_bucket(CSERVER,dir_name,id_bucket,init_key,fin_key);
			fprintf(stdout, "criou bucket %s no intervalo %d até %d\n",id_bucket,init_key,fin_key);
			init_key = fin_key +1;
    }
	}else if(strcmp(CSERVER,"SRVSC") == 0){
		init_key = 50001;
		strcpy(dir_name,"FNOPOLIS");
		for(i = 1;i <= buck_nbr;i++){
			fin_key = init_key+pair_number;
			snprintf(id_bucket,ID_SIZE,"BUCK%dFP",i);
			ret_oper = create_bucket(CSERVER,dir_name,id_bucket,init_key,fin_key);

			init_key = fin_key +1;
    }
	}else if(strcmp(CSERVER,"SRVSP") == 0){
		//init_key = 75001;
		strcpy(dir_name,"SPAULO");
		for(i = 1;i <= buck_nbr;i++){
			fin_key = init_key+pair_number;
			snprintf(id_bucket,ID_SIZE,"BUCK%dSP",i);
			ret_oper = create_bucket(CSERVER,dir_name,id_bucket,init_key,fin_key);

			init_key = fin_key +1;
    }
	}

	if(ret_oper == 1)
		fprintf(stdout,"[app_create_bucket/app_client.c] O Bucket não foi criado!\n");
}

void app_drop_bucket(){

	printf("DROP Bucket\n");
	printf("id_bucket: ");scanf("%s",id_bucket);

	drop_bucket(id_bucket);
}


int main (int argc, char *argv[]) {

  int it,key;
	TSTAMP_T idTx;

	if(argc >1){
		strcpy(CSERVER,*++argv);
	}else{
		fprintf(stderr,"NECESSARIO INDICAR CSERVER\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout,"CSERVER:%s\n",CSERVER);

	printf("========================================\n\n");

	ret_oper = init_api();
	if(ret_oper == 1){
		printf("Falha na comunicacao com o cluster\n");
		exit(1);
	}

	fprintf(stdout,"Teste das operações para construção do modelo de dados\n");
	//fprintf(stdout,"cria servidor\n");
	//app_create_server();
	fprintf(stdout,"cria diretorios\n");
	app_create_dir();
	fprintf(stdout,"cria buckets\n");
	app_create_bucket();

  fin_api();

	printf("Executado com SUCESSO! \n");
	printf("\n========================================\n");

	return 0;
}
