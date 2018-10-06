#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ID_SIZE 50
#define PAIR_NUMBER 99

void main(){

  int i,init_key,fin_key,buck_nbr,it1,it2;
  char id_bucket[ID_SIZE];
  int b_number,pair_number;
  //char val[sdata_f];
  char buffer[61];
  FILE *sdata_f;	
  int key;
  char key_c[10],valor[51];
   	

  b_number = 50;
  pair_number = 99;
  init_key = 1;

  //0000000000AAAAAAAAAAAA(10+50)
  sdata_f = fopen("database.dat","w");
		
  for(it1 = 1; it1 <= b_number ;it1++){
    fin_key = init_key + pair_number;

    //printf("bucket %d  faixa: %d ate %d\n",it1,init_key,fin_key);		
    for(it2 = init_key; it2 <= fin_key; it2++){
      fprintf(sdata_f,"%10d%s%d\n",it2,"VALORDACHAVE",it2);
    }

    init_key = fin_key +1;
  }
  fclose(sdata_f);

  sdata_f = fopen("database.dat","r");
	
  while( fgets(buffer,61,sdata_f) != NULL ){
    memmove(key_c,buffer,10);
    key = atoi(key_c);
    memmove(valor,buffer+10,50);
    printf("key:%d value:%s",key,valor);
  }	

}
