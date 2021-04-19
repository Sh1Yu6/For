
/************************************************
#
#      Filename: ptherad.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-15 11:30:42
# Last Modified: 2021-04-15 15:45:23
#***********************************************/
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>
using namespace std;

pthread_mutex_t mutex;
int n = 0;

void* func1(void* v){
    for(int i = 0; i < 10000; ++i){
        pthread_mutex_lock( &mutex );
        ++n;
        pthread_mutex_unlock( &mutex );
    }
    cout << n << endl;
    return nullptr;
}

void* func2(void* v){
    for(int i = 0; i < 10000; ++i){
        pthread_mutex_lock( &mutex );
        ++n;
        pthread_mutex_unlock( &mutex );
    }
    cout << n << endl;
    return nullptr;
}


int main(int argc, char *argv[])
{
    pthread_mutex_init( &mutex, nullptr );

    pthread_t p[2];
    pthread_create( &p[0], nullptr, func1, nullptr );
    pthread_create( &p[1], nullptr, func2, nullptr );

    pthread_join(p[0], nullptr);
    pthread_join(p[1], nullptr);

    pthread_mutex_destroy( &mutex );
    return 0;
}

