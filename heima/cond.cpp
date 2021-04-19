
/************************************************
#
#      Filename: rwlock.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-15 16:38:26
# Last Modified: 2021-04-15 17:10:05
#***********************************************/
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

pthread_cond_t cond;
pthread_mutex_t mutex;

int n = 5;

void* func1(void*){
    while(true){
        pthread_mutex_lock(&mutex);
        while(n == 5){
            pthread_cond_wait( &cond, &mutex );
        }
        ++n;
        cout << "+ " << n<< endl;
        pthread_cond_signal( &cond );
        pthread_mutex_unlock(&mutex);
        sleep(rand()%2);
    }
}
void* func2(void*){
    while(true){
        pthread_mutex_lock(&mutex);
        while(n == 0){
            pthread_cond_wait( &cond, &mutex );
        }
        --n;
        cout << "- " <<  n << endl;
        pthread_cond_signal( &cond );
        pthread_mutex_unlock(&mutex);
        sleep(rand()%2);
    }
}

int main(int argc, char *argv[])
{
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);
    pthread_t p[2];
    pthread_create( &p[0], nullptr, func1, nullptr );
    pthread_create( &p[1], nullptr, func2, nullptr );


    sleep(5);
    pthread_mutex_destroy( &mutex );
    pthread_cond_destroy( &cond );
    return 0;
}

