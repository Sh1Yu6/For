
/************************************************
#
#      Filename: copy.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-01-26 14:39:21
# Last Modified: 2021-01-26 14:49:09
#***********************************************/
#include <iostream>
#include <fcntl.h>
#include <iterator>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

const int kBufSize = 1024;
int main(int argc, char *argv[])
{
    int inputFd = open(argv[1], O_RDONLY);
    if(inputFd == -1){
        cout << "1" << endl;
    }

    int openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    int outputFd = open(argv[2], openFlags, filePerms);
    if(outputFd == -1){
        cout << "2" << endl;
    }

    char buf[kBufSize];
    ssize_t numRead = 0;
    
    while((numRead = read(inputFd, buf, kBufSize)) > 0){
        if(write(outputFd, buf, numRead) != numRead){
            cout << "couldn't write whole buffer" << endl;
        }
    }

    if(numRead == -1){
        cout << "3" << endl;
    }

    if(close(inputFd) == -1){
        cout << "4" << endl;
    }

    if(close(outputFd) == -1){
        cout << "5" << endl;
    }

    return 0;
}

