
/************************************************
#
#      Filename: testDaemonByAPI.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 15:47:25
# Last Modified: 2021-03-07 15:51:56
#***********************************************/
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main(int argc, char *argv[])
{
    if( daemon( 0, 0 ) == -1 ){
        cout << "error" << endl;
        exit(-1);
    }

    while(true){
        usleep(1000000);
    }
    return 0;
}

