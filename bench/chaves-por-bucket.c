#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ID_SIZE 50
#define PAIR_NUMBER 99

void main(){

  int i,init_key,fin_key,buck_nbr,it1,it2;
  char id_bucket[ID_SIZE];
  int b_number,pair_number;
  char val[50];
	

  b_number = 25;
  pair_number = 100;
  init_key = 1;

		
  for(it1 = 1; it1 <= b_number ;it1++){
    fin_key = init_key + pair_number;

    printf("bucket %d  faixa: %d ate %d\n",it1,init_key,fin_key);		
    for(it2 = init_key; it2 <= fin_key; it2++){
      snprintf(val,ID_SIZE,"VALORDACHAVE%d",it2);
      //printf("inseriu chave %d no bucket %d\n",it2,it1);	
      printf("%d\n",it2);
    }

    init_key = fin_key +1;
  }

}
