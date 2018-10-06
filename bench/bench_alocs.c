#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "alocs/libalocs.h"


#define VAL_SIZE     50


#define TX_NUMBER       3
#define GET_NUMBER      500
#define PUT_NUMBER      500
#define SIZEBUFF21       10
#define SIZEBUFFDB       61
#define KEYPOSDB         10

#define BUCKET_NUMBER 50

//void app_put_pair();
//void app_get_pair();
//void app_remove_pair();

struct thread_info {    /* Used as argument to thread_start() */
  pthread_t thread_id;        /* ID returned by pthread_create() */
  int       thread_num;       /* Application-defined thread # */
	TSTAMP_T id;
  int       key;      /* From command-line argument */
	char      val[VAL_SIZE];
};


clock_t start_oper,stop_oper,start_tx,stop_tx;
clock_t  start_bench,stop_bench;
double elap_put,elap_get,elap_tx,elap_bench;

void tst_funcional();
void init_bench();
void *exec_putoper(void *arg);
void *exec_getoper(void *arg);

void exp1_cen1();
void exp1_cen2();
void exp1_cen3();
void exp1_cen4();
void exp1_cen5();

void exp2_cen1();
void exp2_cen2();
void exp2_cen3();
void exp2_cen4();
void exp2_cen5();

void exp3_cen1();
void exp3_cen2();
void exp3_cen3();
void exp3_cen4();
void exp3_cen5();

void init_time();
void start_time_bench();
void stop_time_bench();
void start_time_tx();
void stop_time_tx();
void start_time_oper();
void stop_time_oper();
double get_elap_time_bench();
double get_elap_time_tx();
double get_elap_time_oper();
void menu1();

int ret_error;

void init_time(){
	elap_put = elap_get = elap_tx = elap_bench = 0;
}

void start_time_bench(){
	start_bench = clock();
}

void stop_time_bench(){
	stop_bench = clock();
}

void start_time_tx(){
	start_tx = clock();
}

void stop_time_tx(){
	stop_tx = clock();
}

void start_time_oper(){
	start_oper = clock();
}

void stop_time_oper(){
	stop_oper = clock();
}

double get_elap_time_bench(){

	return (double) ( (stop_bench - start_bench)* 1000.0) / CLOCKS_PER_SEC;
}

double get_elap_time_tx(){

	return (double) ( (stop_tx - start_tx)* 1000.0) / CLOCKS_PER_SEC;
}

double get_elap_time_oper(){

	return (double) ( (stop_oper - start_oper)* 1000.0) / CLOCKS_PER_SEC;
}

void load_data(){

  int pair_number,it1,it2,key;
  char val[VAL_SIZE],key_c[KEYPOSDB];
  char buffer[SIZEBUFFDB];
  FILE *sdata_f;
  TSTAMP_T id;

  id = begin();

  memset(val,'\0',VAL_SIZE);
  memset(buffer,'\0',SIZEBUFFDB);
  memset(key_c,'\0',KEYPOSDB);

  /*for(it1 = 1; it1 <= BUCKET_NUMBER ;it1++){
    fin_key = init_key + pair_number;


    for(it2 = init_key; it2 <= fin_key; it2++){
      snprintf(val,VAL_SIZE,"VALORDACHAVE%d\0",it2);
      fprintf(stdout,"inserir chave %d\n",it2 );
      ret_error = put_pair(id,it2,val);
      memset(val,'\0',VAL_SIZE);
    }

    init_key = fin_key +1;
  }*/
  sdata_f = fopen("database.dat","r");

  while( fgets(buffer,SIZEBUFFDB,sdata_f) != NULL ){
    memmove(key_c,buffer,KEYPOSDB);
    key = atoi(key_c);
    memmove(val,buffer+KEYPOSDB,VAL_SIZE);
    fprintf(stdout,"inserir chave %d\n",key );

    ret_error = put_pair(id,key,val);

    memset(val,'\0',VAL_SIZE);
    memset(key_c,'\0',KEYPOSDB);
  }

  fclose(sdata_f);

  ret_error = commit(id);

}

void exp3_cen5(){

	/*
		2% de coalocacao
		recuperação de 50 pares (50 pares/bucket)

		apenas consultas
	*/

	int it,it2,key,inc,b_number,r_number,pair_number,init_key,fin_key;
	TSTAMP_T id;
	//struct thread_info *tinfo;
	PAIR_T *pair;
	char val[VAL_SIZE];
	FILE *out_f,*err_f;

	b_number = 1;
	r_number = 50;
	id = 0;
	pair = NULL;
	ret_error = 0;

	pair = malloc(sizeof(PAIR_T));
	if(!pair)
		fprintf(stdout, "Falha ao alocar memoria!\n");

	pair->key = 0;
	pair->value = NULL;

	init_time();

	//load_data();

	//tinfo = NULL;
	start_time_bench();

	out_f = freopen("bench_alocs_exp3_cen5.out", "w+", stdout);
	err_f = freopen("bench_alocs_exp3_cen5.error", "w+", stderr);

	start_time_tx();
	id = begin();

	fprintf(stdout,"\nIniciar Tx para escrita dos pares\n");
	if(id > 0){
		//insere os pares
		//SE
		inc = 1;
		pair_number = 99;
		//init_key = 1;
		//fin_key = (b_number / 2) * (pair_number + 1);

		init_key = 1;
		fin_key = r_number;

		start_time_oper();
		for(it = 1;it <= b_number;it++){
			for(it2 = init_key;it2 <= fin_key;it2++){
        snprintf(val,VAL_SIZE,"VALORDACHAVE%d",it2);
        ret_error = put_pair(id,it2,val);
        if(ret_error)
          fprintf(stdout, "Erro ao inserir par\n");
	    }
		}
		stop_time_oper();

		fprintf(stdout,"\nTempo decorrido para escrita dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
		fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
		fprintf(stdout,"\nTx %d paras execução das atualizações encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Exp 3 Cen 5 (ms):%f\n",get_elap_time_bench());

	freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

	free(pair);
}

void exp3_cen4(){

	/*
		2% de coalocacao
		recuperação de 50 pares (10 pares/bucket)

		apenas consultas
	*/

	int it,it2,key,inc,b_number,r_number,pair_number,init_key,fin_key;
	TSTAMP_T id;
	//struct thread_info *tinfo;
	PAIR_T *pair;
	char val[VAL_SIZE];
	FILE *out_f,*err_f;

	b_number = 5;
	r_number = 10;
	id = 0;
	pair = NULL;
	ret_error = 0;

	pair = malloc(sizeof(PAIR_T));
	if(!pair)
		fprintf(stdout, "Falha ao alocar memoria!\n");

	pair->key = 0;
	pair->value = NULL;

	init_time();

	//load_data();

	//tinfo = NULL;
	start_time_bench();

	out_f = freopen("bench_alocs_exp3_cen4.out", "w+", stdout);
	err_f = freopen("bench_alocs_exp3_cen4.error", "w+", stderr);

	start_time_tx();
	id = begin();

	fprintf(stdout,"\nIniciar Tx para escrita dos pares\n");
	if(id > 0){
		//insere os pares
		//SE
		inc = 1;
		pair_number = 99;
		//init_key = 1;
		//fin_key = (b_number / 2) * (pair_number + 1);

		init_key = 1;
		fin_key = r_number;

		start_time_oper();
		for(it = 1;it <= b_number;it++){
			for(it2 = init_key;it2 <= fin_key;it2++){
        snprintf(val,VAL_SIZE,"VALORDACHAVE%d",it2);
        ret_error = put_pair(id,it2,val);
        if(ret_error)
          fprintf(stdout, "Erro ao inserir par\n");
	    }

			init_key += 100;
			fin_key = init_key + (r_number-1);
		}
		stop_time_oper();

		fprintf(stdout,"\nTempo decorrido para escrita dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
		fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
		fprintf(stdout,"\nTx %d para execução de atualizações encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Exp 3 Cen 4 (ms):%f\n",get_elap_time_bench());

	freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

	free(pair);
}

void exp3_cen3(){

	/*
		2% de coalocacao
		recuperação de 50 pares (5 pares/bucket)

		apenas consultas
	*/

	int it,it2,key,inc,b_number,r_number,pair_number,init_key,fin_key;
	TSTAMP_T id;
	//struct thread_info *tinfo;
	PAIR_T *pair;
	char val[VAL_SIZE];
	FILE *out_f,*err_f;

	b_number = 10;
	r_number = 5;
	id = 0;
	pair = NULL;
	ret_error = 0;

	pair = malloc(sizeof(PAIR_T));
	if(!pair)
		fprintf(stdout, "Falha ao alocar memoria!\n");

	pair->key = 0;
	pair->value = NULL;

	init_time();

	//load_data();

	//tinfo = NULL;
	start_time_bench();

	out_f = freopen("bench_alocs_exp3_cen3.out", "w+", stdout);
	err_f = freopen("bench_alocs_exp3_cen3.error", "w+", stderr);

	start_time_tx();
	id = begin();

	fprintf(stdout,"\nIniciar Tx para consulta dos pares\n");
	if(id > 0){
		//insere os pares
		//SE
		inc = 1;
		pair_number = 99;
		//init_key = 1;
		//fin_key = (b_number / 2) * (pair_number + 1);

		init_key = 1;
		fin_key = r_number;

		start_time_oper();
		for(it = 1;it <= b_number;it++){
			for(it2 = init_key;it2 <= fin_key;it2++){
        snprintf(val,VAL_SIZE,"VALORDACHAVE%d",it2);
        ret_error = put_pair(id,it2,val);
        if(ret_error)
          fprintf(stdout, "Erro ao inserir par\n");
	    }

			init_key += 100;
			fin_key = init_key + (r_number-1);
		}
		stop_time_oper();

		fprintf(stdout,"\nTempo decorrido para escrita dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
		fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
		fprintf(stdout,"\nTx %d para execução de atualições encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para do Exp 3 Cen 3 (ms):%f\n",get_elap_time_bench());

	freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

	free(pair);
}

void exp3_cen2(){

  /*
    2% de coalocacao
    recuperação de 50 pares (2 pares/bucket) 25 buckets

    apenas consultas
  */

  int it,it2,key,inc,b_number,r_number,pair_number,init_key,fin_key;
  TSTAMP_T id;
  //struct thread_info *tinfo;
  PAIR_T *pair;
  char val[VAL_SIZE];
  FILE *out_f,*err_f;

	b_number = 25;
	r_number = 2;
	id = 0;
  pair = NULL;
	ret_error = 0;

  pair = malloc(sizeof(PAIR_T));
  if(!pair)
    fprintf(stdout, "Falha ao alocar memoria!\n");

  pair->key = 0;
  pair->value = NULL;

  init_time();

  //load_data();

	out_f = freopen("bench_alocs_exp3_cen2.out", "w+", stdout);
  err_f = freopen("bench_alocs_exp3_cen2.error", "w+", stderr);

  //tinfo = NULL;
  start_time_bench();

  start_time_tx();
  id = begin();

  fprintf(stdout,"\nIniciar Tx para consulta dos pares\n");
  if(id > 0){
    //insere os pares
		//SE
		inc = 1;
		pair_number = 99;
		init_key = 1;
		fin_key = r_number;

		start_time_oper();
		for(it = 1;it <= b_number;it++){
			for(it2 = init_key;it2 <= fin_key;it2++){
        snprintf(val,VAL_SIZE,"VALORDACHAVE%d",it2);
        ret_error = put_pair(id,it2,val);
        if(ret_error)
          fprintf(stdout, "Erro ao inserir par\n");
	    }

			init_key += 100;
			fin_key = init_key + (r_number-1);
		}
    stop_time_oper();

  	fprintf(stdout,"\nTempo decorrido para escrita dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
    fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
    fprintf(stdout,"\nTx %d para execução das atualizações encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Exp 3 Cen 2 (ms):%f\n",get_elap_time_bench());

  freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

  free(pair);
}

void exp3_cen1(){

	/*
    1% de coalocacao
    recuperação de 50 pares (1 par/bucket) 50 buckets

    apenas consultas
  */

  int it,it2,key,inc,w_number,r_number;
  TSTAMP_T id;
  //struct thread_info *tinfo;
  PAIR_T *pair;
  char val[VAL_SIZE];
  FILE *out_f,*err_f;

  r_number = BUCKET_NUMBER;
	id = 0;
  pair = NULL;
	ret_error = 0;

  pair = malloc(sizeof(PAIR_T));
  if(!pair)
    fprintf(stdout, "Falha ao alocar memoria!\n");

  pair->key = 0;
  pair->value = NULL;

  init_time();

  //load_data();

  //tinfo = NULL;
  start_time_bench();

  out_f = freopen("bench_alocs_exp3_cen1.out", "w+", stdout);
  err_f = freopen("bench_alocs_exp3_cen1.error", "w+", stderr);


  start_time_tx();
  id = begin();

  fprintf(stdout,"\nIniciar Tx para escrita dos pares\n");
  if(id > 0){
    //insere os pares
		//SE
		inc = 1;
		start_time_oper();
		for(it2 = 1;it2 <= r_number;it2++){
      key = ((it2 > 1)? (it2 + inc) : it2);
      snprintf(val,VAL_SIZE,"VALORDACHAVE%d",it2);
      ret_error = put_pair(id,key,val);
      if(ret_error)
        fprintf(stdout, "Erro ao inserir par\n");

      inc += 100;
    }
    stop_time_oper();

  	fprintf(stdout,"\nTempo decorrido para escrita dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
    fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
    fprintf(stdout,"\nTx %d com execução de atualizações encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Exp 3 Cen 1 (ms):%f\n",get_elap_time_bench());

  freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

  free(pair);

}



void exp2_cen4(){

  /*
		efeito do cache
		recuperação de 50 pares (5 pares/bucket) 10 bucket
    variavel = tamanho do cache => 10
		apenas consultas
	*/

  /*
		efeito do cache
		recuperação de 50 pares (5 pares/bucket) 10 bucket
    variavel = tamanho do cache => 10
		apenas consultas
	*/

	int it,it2,key,r_number;
  int *keys;
	TSTAMP_T id;
	//struct thread_info *tinfo;
	PAIR_T *pair;
	char val[VAL_SIZE];
	FILE *out_f,*err_f,*sdata_f;
  char buffer[SIZEBUFF21];

	r_number = 50;
	ret_error = id = 0;
	pair = NULL;
  sdata_f = NULL;

	pair = malloc(sizeof(PAIR_T));
	if(!pair){
		fprintf(stdout, "Falha ao alocar memoria!\n");
    exit(EXIT_FAILURE);
  }

  keys = malloc(sizeof(int) * r_number);
  if(!keys){
    fprintf(stdout, "Falha ao alocar memoria!\n");
    exit(EXIT_FAILURE);
  }

	pair->key = 0;
	pair->value = NULL;

	init_time();

	//tinfo = NULL;
	out_f = freopen("bench_alocs_exp2_cen4.out", "w+", stdout);
	err_f = freopen("bench_alocs_exp2_cen4.error", "w+", stderr);

  //abre arquivo com as chaves que serão consultadas
  sdata_f = fopen("source_data21.dat","r");
  if(!sdata_f){
     fprintf(stdout,"Error opening file\n");
     exit(EXIT_FAILURE);
  }

  it = 0;
  while( fgets(buffer,SIZEBUFF21,sdata_f) != NULL )
    keys[it++] = atoi(buffer);

  start_time_bench();

  start_time_tx();
	id = begin();

	fprintf(stdout,"\nIniciar Tx para consulta dos pares\n");
	if(id > 0){
		start_time_oper();
		for(it = 0;it < r_number;it++){
      ret_error = get_pair(id,keys[it],pair);
      if(!ret_error && (pair->key > 0) )
        fprintf(stdout,"Par encontrado: key:%d value:%s\n",pair->key,pair->value);
      else
				fprintf(stdout,"Chave não encontrada!\n");
    }
		stop_time_oper();

		fprintf(stdout,"\nTempo decorrido para consulta dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
		fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
		fprintf(stdout,"\nTx %d com execução de consulta encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Exp 2 Cenário 4 (ms):%f\n",get_elap_time_bench());

	freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

  fclose(sdata_f);

	free(pair);
  free(keys);
}

void exp2_cen3(){

  /*
		efeito do cache
		recuperação de 50 pares (5 pares/bucket) 10 bucket
    variavel = tamanho do cache => 6
		apenas consultas
	*/

	int it,it2,key,r_number;
  int *keys;
	TSTAMP_T id;
	//struct thread_info *tinfo;
	PAIR_T *pair;
	char val[VAL_SIZE];
	FILE *out_f,*err_f,*sdata_f;
  char buffer[SIZEBUFF21];

	r_number = 50;
	ret_error = id = 0;
	pair = NULL;
  sdata_f = NULL;

	pair = malloc(sizeof(PAIR_T));
	if(!pair){
		fprintf(stdout, "Falha ao alocar memoria!\n");
    exit(EXIT_FAILURE);
  }

  keys = malloc(sizeof(int) * r_number);
  if(!keys){
    fprintf(stdout, "Falha ao alocar memoria!\n");
    exit(EXIT_FAILURE);
  }

	pair->key = 0;
	pair->value = NULL;

	init_time();

	//tinfo = NULL;
	out_f = freopen("bench_alocs_exp2_cen3.out", "w+", stdout);
	err_f = freopen("bench_alocs_exp2_cen3.error", "w+", stderr);

  //abre arquivo com as chaves que serão consultadas
  sdata_f = fopen("source_data21.dat","r");
  if(!sdata_f){
     fprintf(stdout,"Error opening file\n");
     exit(EXIT_FAILURE);
  }

  it = 0;
  while( fgets(buffer,SIZEBUFF21,sdata_f) != NULL )
    keys[it++] = atoi(buffer);

  start_time_bench();

  start_time_tx();
	id = begin();

	fprintf(stdout,"\nIniciar Tx para consulta dos pares\n");
	if(id > 0){
		start_time_oper();
		for(it = 0;it < r_number;it++){
      ret_error = get_pair(id,keys[it],pair);
      if(!ret_error && (pair->key > 0) )
        fprintf(stdout,"Par encontrado: key:%d value:%s\n",pair->key,pair->value);
      else
				fprintf(stdout,"Chave não encontrada!\n");
    }
		stop_time_oper();

		fprintf(stdout,"\nTempo decorrido para consulta dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
		fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
		fprintf(stdout,"\nTx %d com execução de consulta encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Exp 2 Cenário 3 (ms):%f\n",get_elap_time_bench());

	freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);
  fclose(sdata_f);

	free(pair);
  free(keys);
}

void exp2_cen2(){

  /*
		efeito do cache
		recuperação de 50 pares (5 pares/bucket) 10 bucket
    variavel = tamanho do cache => 3
		apenas consultas
	*/

	int it,it2,key,r_number;
  int *keys;
	TSTAMP_T id;
	//struct thread_info *tinfo;
	PAIR_T *pair;
	char val[VAL_SIZE];
	FILE *out_f,*err_f,*sdata_f;
  char buffer[SIZEBUFF21];

	r_number = 50;
	ret_error = id = 0;
	pair = NULL;
  sdata_f = NULL;

	pair = malloc(sizeof(PAIR_T));
	if(!pair){
		fprintf(stdout, "Falha ao alocar memoria!\n");
    exit(EXIT_FAILURE);
  }

  keys = malloc(sizeof(int) * r_number);
  if(!keys){
    fprintf(stdout, "Falha ao alocar memoria!\n");
    exit(EXIT_FAILURE);
  }

	pair->key = 0;
	pair->value = NULL;

	init_time();

	//tinfo = NULL;
	out_f = freopen("bench_alocs_exp2_cen2.out", "w+", stdout);
	err_f = freopen("bench_alocs_exp2_cen2.error", "w+", stderr);

  //abre arquivo com as chaves que serão consultadas
  sdata_f = fopen("source_data21.dat","r");
  if(!sdata_f){
     fprintf(stdout,"Error opening file\n");
     exit(EXIT_FAILURE);
  }

  it = 0;
  while( fgets(buffer,SIZEBUFF21,sdata_f) != NULL )
    keys[it++] = atoi(buffer);

  start_time_bench();

  start_time_tx();
	id = begin();

	fprintf(stdout,"\nIniciar Tx para consulta dos pares\n");
	if(id > 0){
		start_time_oper();
		for(it = 0;it < r_number;it++){
      ret_error = get_pair(id,keys[it],pair);
      if(!ret_error && (pair->key > 0) )
        fprintf(stdout,"Par encontrado: key:%d value:%s\n",pair->key,pair->value);
      else
				fprintf(stdout,"Chave não encontrada!\n");
    }
		stop_time_oper();

		fprintf(stdout,"\nTempo decorrido para consulta dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
		fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
		fprintf(stdout,"\nTx %d com execução de consulta encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Exp 2 Cenário 2 (ms):%f\n",get_elap_time_bench());

	freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

  fclose(sdata_f);

	free(pair);
  free(keys);

}

void exp2_cen1(){

	/*
		efeito do cache
		recuperação de 50 pares (5 pares/bucket) 10 bucket
    variavel = tamanho do cache => 1
		apenas consultas
	*/

	int it,it2,key,r_number;
  int *keys;
	TSTAMP_T id;
	//struct thread_info *tinfo;
	PAIR_T *pair;
	char val[VAL_SIZE];
	FILE *out_f,*err_f,*sdata_f;
  char buffer[SIZEBUFF21];

	r_number = 50;
	ret_error = id = 0;
	pair = NULL;
  sdata_f = NULL;

	pair = malloc(sizeof(PAIR_T));
	if(!pair){
		fprintf(stdout, "Falha ao alocar memoria!\n");
    exit(EXIT_FAILURE);
  }

  keys = malloc(sizeof(int) * r_number);
  if(!keys){
    fprintf(stdout, "Falha ao alocar memoria!\n");
    exit(EXIT_FAILURE);
  }

	pair->key = 0;
	pair->value = NULL;

	init_time();

	//tinfo = NULL;
	out_f = freopen("bench_alocs_exp2_cen1.out", "w+", stdout);
	err_f = freopen("bench_alocs_exp2_cen1.error", "w+", stderr);

  //abre arquivo com as chaves que serão consultadas
  sdata_f = fopen("source_data21.dat","r");
  if(!sdata_f){
     fprintf(stdout,"Error opening file\n");
     exit(EXIT_FAILURE);
  }

  it = 0;
  while( fgets(buffer,SIZEBUFF21,sdata_f) != NULL )
    keys[it++] = atoi(buffer);

  start_time_bench();

  start_time_tx();
	id = begin();

	fprintf(stdout,"\nIniciar Tx para consulta dos pares\n");
	if(id > 0){
		start_time_oper();
		for(it = 0;it < r_number;it++){
      ret_error = get_pair(id,keys[it],pair);
      if(!ret_error && (pair->key > 0) )
        fprintf(stdout,"Par encontrado: key:%d value:%s\n",pair->key,pair->value);
      else
				fprintf(stdout,"Chave não encontrada!\n");
    }
		stop_time_oper();

		fprintf(stdout,"\nTempo decorrido para consulta dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
		fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
		fprintf(stdout,"\nTx %d com execução de consulta encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Exp 2 Cenário 1 (ms):%f\n",get_elap_time_bench());

	freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

  fclose(sdata_f);

	free(pair);
  free(keys);
}

void exp1_cen5(){

	/*
		2% de coalocacao
		recuperação de 50 pares (50 pares/bucket)

		apenas consultas
	*/

	int it,it2,key,inc,b_number,r_number,pair_number,init_key,fin_key;
	TSTAMP_T id;
	//struct thread_info *tinfo;
	PAIR_T *pair;
	char val[VAL_SIZE];
	FILE *out_f,*err_f;

	b_number = 1;
	r_number = 50;
	id = 0;
	pair = NULL;
	ret_error = 0;

	pair = malloc(sizeof(PAIR_T));
	if(!pair)
		fprintf(stdout, "Falha ao alocar memoria!\n");

	pair->key = 0;
	pair->value = NULL;

	init_time();

	//load_data();

	//tinfo = NULL;
	start_time_bench();

	out_f = freopen("bench_alocs_exp1_cen5.out", "w+", stdout);
	err_f = freopen("bench_alocs_exp1_cen5.error", "w+", stderr);

	start_time_tx();
	id = begin();

	fprintf(stdout,"\nIniciar Tx para consulta dos pares\n");
	if(id > 0){
		//insere os pares
		//SE
		inc = 1;
		pair_number = 99;
		//init_key = 1;
		//fin_key = (b_number / 2) * (pair_number + 1);

		init_key = 1;
		fin_key = r_number;

		start_time_oper();
		for(it = 1;it <= b_number;it++){
			for(it2 = init_key;it2 <= fin_key;it2++){
	      ret_error = get_pair(id,it2,pair);
	      if(!ret_error && (pair->key > 0) )
	        fprintf(stdout,"Par encontrado: key:%d value:%s\n",pair->key,pair->value);
	      else
					fprintf(stdout,"Chave não encontrada!\n");
	    }
		}
		stop_time_oper();

		fprintf(stdout,"\nTempo decorrido para consulta dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
		fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
		fprintf(stdout,"\nTx %d com execução de consulta encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Exp 1 Cenário 5 (ms):%f\n",get_elap_time_bench());

	freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

	free(pair);
}

void exp1_cen4(){

	/*
		2% de coalocacao
		recuperação de 50 pares (10 pares/bucket)

		apenas consultas
	*/

	int it,it2,key,inc,b_number,r_number,pair_number,init_key,fin_key;
	TSTAMP_T id;
	//struct thread_info *tinfo;
	PAIR_T *pair;
	char val[VAL_SIZE];
	FILE *out_f,*err_f;

	b_number = 5;
	r_number = 10;
	id = 0;
	pair = NULL;
	ret_error = 0;

	pair = malloc(sizeof(PAIR_T));
	if(!pair)
		fprintf(stdout, "Falha ao alocar memoria!\n");

	pair->key = 0;
	pair->value = NULL;

	init_time();

	//load_data();

	//tinfo = NULL;
	start_time_bench();

	out_f = freopen("bench_alocs_exp1_cen4.out", "w+", stdout);
	err_f = freopen("bench_alocs_exp1_cen4.error", "w+", stderr);

	start_time_tx();
	id = begin();

	fprintf(stdout,"\nIniciar Tx para consulta dos pares\n");
	if(id > 0){
		//insere os pares
		//SE
		inc = 1;
		pair_number = 99;
		//init_key = 1;
		//fin_key = (b_number / 2) * (pair_number + 1);

		init_key = 1;
		fin_key = r_number;

		start_time_oper();
		for(it = 1;it <= b_number;it++){
			for(it2 = init_key;it2 <= fin_key;it2++){
	      ret_error = get_pair(id,it2,pair);
	      if(!ret_error && (pair->key > 0) )
	        fprintf(stdout,"Par encontrado: key:%d value:%s\n",pair->key,pair->value);
	      else
					fprintf(stdout,"Chave não encontrada!\n");
	    }

			init_key += 100;
			fin_key = init_key + (r_number-1);
		}
		stop_time_oper();

		fprintf(stdout,"\nTempo decorrido para consulta dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
		fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
		fprintf(stdout,"\nTx %d com execução de consulta encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Cenário 4 (ms):%f\n",get_elap_time_bench());

	freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

	free(pair);
}

void exp1_cen3(){

	/*
		2% de coalocacao
		recuperação de 50 pares (5 pares/bucket)

		apenas consultas
	*/

	int it,it2,key,inc,b_number,r_number,pair_number,init_key,fin_key;
	TSTAMP_T id;
	//struct thread_info *tinfo;
	PAIR_T *pair;
	char val[VAL_SIZE];
	FILE *out_f,*err_f;

	b_number = 10;
	r_number = 5;
	id = 0;
	pair = NULL;
	ret_error = 0;

	pair = malloc(sizeof(PAIR_T));
	if(!pair)
		fprintf(stdout, "Falha ao alocar memoria!\n");

	pair->key = 0;
	pair->value = NULL;

	init_time();

	//load_data();

	//tinfo = NULL;
	start_time_bench();

	out_f = freopen("bench_alocs_exp1_cen3.out", "w+", stdout);
	err_f = freopen("bench_alocs_exp1_cen3.error", "w+", stderr);

	start_time_tx();
	id = begin();

	fprintf(stdout,"\nIniciar Tx para consulta dos pares\n");
	if(id > 0){
		//insere os pares
		//SE
		inc = 1;
		pair_number = 99;
		//init_key = 1;
		//fin_key = (b_number / 2) * (pair_number + 1);

		init_key = 1;
		fin_key = r_number;

		start_time_oper();
		for(it = 1;it <= b_number;it++){
			for(it2 = init_key;it2 <= fin_key;it2++){
	      ret_error = get_pair(id,it2,pair);
	      if(!ret_error && (pair->key > 0) )
	        fprintf(stdout,"Par encontrado: key:%d value:%s\n",pair->key,pair->value);
	      else
					fprintf(stdout,"Chave não encontrada!\n");
	    }

			init_key += 100;
			fin_key = init_key + (r_number-1);
		}
		stop_time_oper();

		fprintf(stdout,"\nTempo decorrido para consulta dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
		fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
		fprintf(stdout,"\nTx %d com execução de consulta encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Cenário 3 (ms):%f\n",get_elap_time_bench());

	freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

	free(pair);
}

void exp1_cen2(){

  /*
    2% de coalocacao
    recuperação de 50 pares (2 pares/bucket) 25 buckets

    apenas consultas
  */

  int it,it2,key,inc,b_number,r_number,pair_number,init_key,fin_key;
  TSTAMP_T id;
  //struct thread_info *tinfo;
  PAIR_T *pair;
  char val[VAL_SIZE];
  FILE *out_f,*err_f;

	b_number = 25;
	r_number = 2;
	id = 0;
  pair = NULL;
	ret_error = 0;

  pair = malloc(sizeof(PAIR_T));
  if(!pair)
    fprintf(stdout, "Falha ao alocar memoria!\n");

  pair->key = 0;
  pair->value = NULL;

  init_time();

  //load_data();

	out_f = freopen("bench_alocs_exp1_cen2.out", "w+", stdout);
  err_f = freopen("bench_alocs_exp1_cen2.error", "w+", stderr);

  //tinfo = NULL;
  start_time_bench();

  start_time_tx();
  id = begin();

  fprintf(stdout,"\nIniciar Tx para consulta dos pares\n");
  if(id > 0){
    //insere os pares
		//SE
		inc = 1;
		pair_number = 99;
		init_key = 1;
		fin_key = r_number;

		start_time_oper();
		for(it = 1;it <= b_number;it++){
			for(it2 = init_key;it2 <= fin_key;it2++){
	      ret_error = get_pair(id,it2,pair);
	      if(!ret_error && (pair->key > 0) )
	        fprintf(stdout,"Par encontrado: key:%d value:%s\n",pair->key,pair->value);
	      else
					fprintf(stdout,"Chave não encontrada!\n");
	    }

			init_key += 100;
			fin_key = init_key + (r_number-1);
		}
    stop_time_oper();

  	fprintf(stdout,"\nTempo decorrido para consulta dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
    fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
    fprintf(stdout,"\nTx %d com execução de consulta encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Cenário 2 (ms):%f\n",get_elap_time_bench());

  freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

  free(pair);
}

void exp1_cen1(){

	/*
    1% de coalocacao
    recuperação de 50 pares (1 par/bucket) 50 buckets

    apenas consultas
  */

  int it,it2,key,inc,w_number,r_number;
  TSTAMP_T id;
  //struct thread_info *tinfo;
  PAIR_T *pair;
  char val[VAL_SIZE];
  FILE *out_f,*err_f;

  r_number = BUCKET_NUMBER;
	id = 0;
  pair = NULL;
	ret_error = 0;

  pair = malloc(sizeof(PAIR_T));
  if(!pair)
    fprintf(stdout, "Falha ao alocar memoria!\n");

  pair->key = 0;
  pair->value = NULL;

  init_time();

  //load_data();

  //tinfo = NULL;
  start_time_bench();

  out_f = freopen("bench_alocs_exp1_cen1.out", "w+", stdout);
  err_f = freopen("bench_alocs_exp1_cen1.error", "w+", stderr);


  start_time_tx();
  id = begin();

  fprintf(stdout,"\nIniciar Tx para consulta dos pares\n");
  if(id > 0){
    //insere os pares
		//SE
		inc = 1;
		start_time_oper();
		for(it2 = 1;it2 <= r_number;it2++){
      key = (it2 + inc);
      ret_error = get_pair(id,key,pair);
      if(!ret_error && (pair->key > 0) )
        fprintf(stdout,"Par encontrado: key:%d value:%s\n",pair->key,pair->value);
      else
				fprintf(stdout,"Chave não encontrada!\n");

      inc += 100;
    }
    stop_time_oper();

  	fprintf(stdout,"\nTempo decorrido para consulta dos pares (ms):%f\n",get_elap_time_oper());

		start_time_oper();
		ret_error = commit(id);
		stop_time_oper();

		stop_time_tx();
    fprintf(stdout,"\nTempo decorrido para execução do commit:%f\n",get_elap_time_oper());
    fprintf(stdout,"\nTx %d com execução de consulta encerrada, em %f (ms) \n",id,get_elap_time_tx());
	}else{
		fprintf(stdout,"falha ao iniciar Tx %d \n",id);
		exit(EXIT_FAILURE);
	}

	stop_time_bench();
	fprintf(stdout,"\nTempo decorrido para execução do Cenário 1 (ms):%f\n",get_elap_time_bench());

  freopen("/dev/null","r+",stdout);
  freopen("/dev/null","r+",stderr);

  free(pair);

}

void init_bench(){

  int op;

  op = 0;
	while(op != 16){
		printf("\n");
		printf("\n1  -  Criar Base de Dados");
    printf("\n2  -  Exp 1 - Cenario 1");
		printf("\n3  -  Exp 1 - Cenario 2");
    printf("\n4  -  Exp 1 - Cenario 3");
		printf("\n5  -  Exp 1 - Cenario 4");
		printf("\n6  -  Exp 1 - Cenario 5");
    printf("\n---------------------");
    printf("\n7  -  Exp 2 - Cenario 1");
		printf("\n8  -  Exp 2 - Cenario 2");
    printf("\n9  -  Exp 2 - Cenario 3");
    printf("\n10  -  Exp 2 - Cenario 4");
    printf("\n---------------------");
    printf("\n11 - Exp 3 - Cenario 1");
		printf("\n12 - Exp 3 - Cenario 2");
    printf("\n13 - Exp 3 - Cenario 3");
		printf("\n14 - Exp 3 - Cenario 4");
		printf("\n15 - Exp 3 - Cenario 5");

    printf("\n16 - Voltar");

		printf("\nOperacao:");scanf("%d",&op);
		if(op == 1)
			load_data();
    else if(op == 2)
			exp1_cen1();
		else if(op == 3)
			exp1_cen2();
    else if(op == 4)
  		exp1_cen3();
		else if(op == 5)
	  	exp1_cen4();
		else if(op == 6)
		  exp1_cen5();
    else if(op == 7)
  		exp2_cen1();
    else if(op == 8)
    	exp2_cen2();
    else if(op == 9)
      exp2_cen3();
    else if(op == 10)
      exp2_cen4();
    else if(op == 11)
  		exp3_cen1();
    else if(op == 12)
      exp3_cen2();
    else if(op == 13)
  		exp3_cen3();
    else if(op == 14)
  		exp3_cen4();
    else if(op == 15)
  		exp3_cen5();
  }

}

void *exec_putoper(void *arg){
	struct thread_info *tinfo;
	int ret;

	ret_error= 0;
	tinfo = (struct thread_info *) arg;

	ret_error= put_pair(tinfo->id,tinfo->key,tinfo->val);

}

void *exec_getoper(void *arg){
	struct thread_info *tinfo;
	PAIR_T pair;
	int ret;

	ret_error= 0;
	tinfo = (struct thread_info *) arg;

	if( (ret_error= get_pair(tinfo->id,tinfo->key,&pair)) == 1 )
		fprintf(stdout,"Chave não encontrada!\n");

}

void tst_funcional(){

	int it,it2,key;
	TSTAMP_T id;
	char val[VAL_SIZE];
	PAIR_T pair;

	id = 0;
	for(it = 1;it <= TX_NUMBER;it++){

		fprintf(stdout,"Tx %d iniciada\n",id);
		if(id > 0){
			//insere os pares
			fprintf(stdout,"Inserção dos pares na tx %d\n",it);
			for(it2 = 1;it2 <= PUT_NUMBER;it2++){
				key = (it2 + 1000);
				snprintf(val,VAL_SIZE,"VALORDACHAVE%d",key);
				ret_error= put_pair(id,key,val);
			}
			fprintf(stdout,"\nFim Inserção dos Pares\nConsulta dos pares\n");

			for(it2 = 1;it2 <= GET_NUMBER;it2++){
				key = (it2 + 1000);
				if( (ret_error= get_pair(id,key,&pair)) == 1 )
					fprintf(stdout,"Chave não encontrada!\n");
			}

			ret_error= commit(id);
		}else
			fprintf(stdout,"falha ao iniciar Tx %d \n",id);

		fprintf(stdout,"Tx %d encerrada\n",id);
	}

}

void menu1(){

  int op;

  op = 0;
	while(op != 3){
		printf("\n");
		printf("\n1 - Realizar teste funcional");
		printf("\n2 - Benchmarking");
		printf("\n3 - fim");

    printf("\nOperacao:");scanf("%d",&op);
		if(op == 1)
			tst_funcional();
		else if(op == 2)
			init_bench();
  }
}

int main () {



	printf("========================================\n\n");
	fprintf(stdout,"Aplicação para Benchmarking do Alocs\n");

  ret_error = 0;
	ret_error= init_api();
	if(ret_error == 1){
		printf("Falha na comunicacao com o cluster\n");
		exit(1);
	}

  menu1();

  fin_api();

	printf("Executado com SUCESSO! \n");
	printf("\n========================================\n");

	return 0;
}
