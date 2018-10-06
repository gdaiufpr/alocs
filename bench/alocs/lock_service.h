#include "alocs_conf.h"
#include <semaphore.h>
#include <time.h>

#ifndef LOCK_SERVICE_H
#define LOCK_SERVICE_H


/*prototipo int get_post(sem_t*)
 * descricao: libera a regiao exclusiva para o proximo processo
 * parametros: sem_t *sem semaforo utilizado para controlar a regiao exclusiva
 * retorno: um inteiro indicativo de falha ou sucesso*/
int get_post(sem_t *sem);

/*prototipo int get_post(sem_t*)
 * descricao: bloqueia a regiao exclusiva controlada por sem, para o processo que solicitou entrada
 * parametros: sem_t *sem semaforo utilizado para controlar a regiao exclusiva
 * retorno: um inteiro indicativo de falha ou sucesso*/
int get_wait(sem_t *sem);

/*prototipo void init_semaphore(sem_t *sem,int shared,int init_value)
 * descricao: inicializa os semaforos para controlar as regiões exclusivas
 * parametros: sem_t *sem -> semaforo que sera inicializado
               int shared -> indica se o semaforo e compartilhado entre processos
               int init_value -> valor inicial do semaforo
 * retorno: um inteiro indicativo de falha ou sucesso*/
void init_semaphore(sem_t *sem,int shared,int init_value);

#endif
