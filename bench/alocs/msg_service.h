#include "alocs_conf.h"
#include "ccurr_control.h"
#include "storage.h"
#include "msg_service_req.h"
//#include <sys/time.h>
//#include <signal.h>
#include <pthread.h>

#ifndef MSG_SERVICE_H
#define MSG_SERVICE_H

const char *ALL_SERVERS[] =  {"PARANA","RGSUL","SCATARINA","SAOPAULO"};
const char *END_POINTS[] =  {"tcp://app_alocs1:5570","tcp://app_alocs2:5570","tcp://app_alocs3:5570","tcp://app_alocs4:5570"};

typedef enum TYPE_MSG_E TYPE_MSG_T;
enum TYPE_MSG_E{
  CLOCK_REQ = 0,
  BUCKET_REQ = 1,
  VALIDATION_REQ = 2,
  REGISTER_REQ = 3,
  ENDCOMM_REQ = 4,
  ABORT_REQ = 5
};

/* referencia para cmzq
goo.gl/ACpg85
*/

#ifndef ZMQ_DONTWAIT
#   define ZMQ_DONTWAIT     ZMQ_NOBLOCK
#endif
#if ZMQ_VERSION_MAJOR == 2
#   define zmq_msg_send(msg,sock,opt) zmq_send (sock, msg, opt)
#   define zmq_msg_recv(msg,sock,opt) zmq_recv (sock, msg, opt)
#   define zmq_ctx_destroy(context) zmq_term(context)
#   define ZMQ_POLL_MSEC    1000        //  zmq_poll is usec
#   define ZMQ_SNDHWM ZMQ_HWM
#   define ZMQ_RCVHWM ZMQ_HWM
#elif ZMQ_VERSION_MAJOR == 3
#   define ZMQ_POLL_MSEC    1           //  zmq_poll is msec
#endif

#define FRMID_SIZE    10
#define FRMTYPE_SIZE  10
#define CLOCK_SIZE    10
#define THREADS_LIMIT  5
#define BACK_ADDRESS "inproc://backend"
#define FRONT_ADDRESS "tcp://*:5570"
#define REQUEST_TIMEOUT 50000
#define RECVVALID_SIZE 10

/*prototipo: void *send_service(void *param)
 * descricao: função executada via thread para que o Servidor Executor
   envie mensagens para os Servidores Origem (client_task na impl. do 0mq)
 * parametros: args -> parêmetros gerais para execução da thread*/
void *send_service(void *param);

/*prototipo: static void *recv_service(void*)
 * descricao: função executada via thread para que os Servidores Origem
   receba as msgs enviadas pelo Servidor Executor (server_task na impl. do 0mq)
 * parametros: args -> parêmetros gerais para execução da thread*/
void *recv_service(void *args);

TYPE_MSG_T TYPE_MSG;

#endif
