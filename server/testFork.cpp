
/************************************************
#
#      Filename: testFork.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 15:40:35
# Last Modified: 2021-03-07 15:45:26
#***********************************************/
#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
{

    cout << "start" << endl;

    pid_t pid = fork();
    if(pid < 0){
        cout << "can't create subprocess" << endl;
    }else{
        if(pid == 0){
            cout << pid << "     ";
            cout << getppid() << " " << getpid() << endl;
            cout << "I'm subprocess" << endl;
        }else{
            cout << pid << "     ";
            cout << getppid() << " " << getpid() << endl;
            cout << "I'm main process" << endl;
        }
    }
    cout << "end" << endl;
    return 0;
}

