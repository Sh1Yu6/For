
/************************************************
#
#      Filename: ptherad.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-15 11:30:42
# Last Modified: 2021-04-15 15:20:45
#***********************************************/
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>
using namespace std;

void* func1(void* v){
    int a = *(int*) v;
    for(int i = 0; i< a; ++i){
        cout << a << " " << getpid() << " " << pthread_self() << endl;
        sleep(1);
        pthread_testcancel();
    }
    pthread_exit(nullptr);
}

int main(int argc, char *argv[])
{
    pthread_t p1[10];

    int a[10];
    for(int i = 0; i < 10; ++i){
        a[i] = i;
        int ret = pthread_create( &p1[i], nullptr, func1, &a[i] );
        if( ret != 0 ){
            cout << "pthread_create error, " << strerror( ret ) << endl;
            return -1;
        }
    }

    for(int i = 0; i < 10; ++i){
        pthread_join(p1[i], nullptr);
    }

    // 线程分离, 不会产生僵尸进程
    // 自己回收资源
    // pthread_create( 线程, &attr, 函数, 参数 );
    // pthread_attr_t attr;
    // pthread_attr_init(attr);
    // pthread_attr_setdetachstate(attr, );
    // PTHREAD_CREATE_DETACHED PTHREAD_CREATE_JOINABLE
    // pthread_attr_destory(&attr);
    // 
    // pthread_detach(线程);

    // 取消线程
    // pthread_cancel(线程);
    // 线程里面需要有取消点, 才能取消, 到达取消点的时候才能取消
    // pthread_testcancel(void);
    //for(int i = 0; i < 10; ++i){
        //pthread_cancel(p1[i]);
    //}
    //
    // pthread_equal();
    //
    // fork pthread_create
    // exit pthread_exit
    // wait/waitpid pthread_join
    // kill pthread_cancel
    // getpid pthread_self
    //
    //
    //
    //
    return 0;
}

