#!/bin/bash

export ALOCS_DIR=/home/wendel/Documents/academico/mestrado/implementacao/git/alocs
export SRC_DIR=$ALOCS_DIR/client

export JAVA_HOME=/usr/lib64/jdk1.8.0_25
export JAVA_INCLUDE=$JAVA_HOME/include
export LD_LIBRARY_PATH=$JAVA_HOME/jre/lib/amd64/server

rm -f bench_alocs
rm -f bench_alocs.o

#echo $LD_LIBRARY_PATH
gcc -o bench_alocs bench_alocs.c -L$SRC_DIR  -lm -lalocs -lrados -lzmq -lczmq -ljvm -pthread -I$JAVA_INCLUDE -I$JAVA_INCLUDE/linux -L$LD_LIBRARY_PATH
