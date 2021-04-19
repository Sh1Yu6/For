
/************************************************
#
#      Filename: fork.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-13 13:05:25
# Last Modified: 2021-04-13 15:32:17
#***********************************************/
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
using namespace std;

int a = 0;
int main(int argc, char *argv[])
{
    //execl("/bin/ls", "ls", "-lha", nullptr);
    execlp("ls", "ls", "-lha", nullptr);
    return 0;
}

