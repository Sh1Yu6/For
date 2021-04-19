
/************************************************
#
#      Filename: rwlock.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-15 16:38:26
# Last Modified: 2021-04-19 13:39:55
#***********************************************/
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
using namespace std;


sem_t producer;
sem_t consumer;

int n = 0;

void* func1(void*){
    while(true){
        sem_wait(&producer);
        ++n;
        cout << "+ " << n<< endl;
        sem_post(&consumer);
    }
}
void* func2(void*){
    while(true){
        sem_wait(&consumer);
        --n;
        cout << "- " <<  n << endl;
        sem_post(&producer);
    }
}

int main(int argc, char *argv[])
{
    //0 线程 1进程
    sem_init( &producer, 0, 5 );
    sem_init( &consumer, 0, 0 );

    pthread_t p[2];
    pthread_create( &p[0], nullptr, func1, nullptr );
    pthread_create( &p[1], nullptr, func2, nullptr );


    sleep(5);
    return 0;
}

