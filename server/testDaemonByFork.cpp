
/************************************************
#
#      Filename: testDaemon.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 15:21:15
# Last Modified: 2021-03-07 15:38:00
#***********************************************/
#include <iostream>
#include <unistd.h> // fork
#include <cstdlib>
#include <fcntl.h> // open
using namespace std;

void daemonize(){

    if( pid_t pid; ( pid = fork() ) < 0 ){
        cout << "can't create subprocess" << endl;
    }else{
        if(pid != 0){
            exit(0);
        }
    }

    setsid();

    if( chdir("/") < 0 ){
        cout << "can't change dir" << endl;
        exit(-1);
    }

    int fd = open("/dev/null", O_RDWR);
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    return;
}

int main(int argc, char *argv[])
{
    daemonize();

    while(1){
        usleep(1000000);
    }
    return 0;
}

