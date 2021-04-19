
/************************************************
#
#      Filename: rwlock.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-15 16:38:26
# Last Modified: 2021-04-15 16:47:22
#***********************************************/
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

pthread_rwlock_t rwlock;
int main(int argc, char *argv[])
{
    pthread_rwlock_init(&rwlock, nullptr);

    pthread_rwlock_rdlock(&rwlock);
    pthread_rwlock_unlock(&rwlock);

    pthread_rwlock_wrlock(&rwlock);
    pthread_rwlock_unlock(&rwlock);

    pthread_rwlock_destroy(&rwlock);
    return 0;
}

