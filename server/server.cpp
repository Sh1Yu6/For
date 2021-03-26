
/************************************************
#
#      Filename: server.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 14:17:19
# Last Modified: 2021-03-07 14:24:51
#***********************************************/
#include <iostream>
#include <ctime>
#include <unistd.h>
#include "server.h"
using namespace std;

namespace Sh1Yu6{

    Server::Server(){
        cout << "construct..." << endl;
    }

    Server::~Server(){
        cout << "destruct..." << endl;
    }

    void Server::run(){
        while(true){
            cout << "running..." << endl;
            usleep(1000000);
        }
    }

}
