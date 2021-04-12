
/************************************************
#
#      Filename: error.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-12 14:35:29
# Last Modified: 2021-04-12 14:43:50
#***********************************************/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
using namespace std;

int main(int argc, char *argv[])
{
    int fd = open("makefile.txt", O_RDWR);
    if( fd < 0 ){
        perror("open failed:");
    }
    char buff[1024];
    int count = 0;
    while( ( count = read( fd, buff, 1024 ) ) ){

    }
    cout << "a" << endl;
    close(fd);
    return 0;
}

