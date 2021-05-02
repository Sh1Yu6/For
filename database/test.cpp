
/************************************************
#
#      Filename: test.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-24 10:03:01
# Last Modified: 2021-04-24 10:15:57
#***********************************************/
#include <iostream>
#include <mysql/mysql.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{

    auto my = mysql_init(nullptr);
    if( my == nullptr ){
        cout << "init error" << endl;
        exit(1);
    }

    auto r = mysql_real_connect(my, "127.0.0.1", "root", 
            "123", "p_test", 0, nullptr, 0);
    if( r == nullptr ){
        cout << "connect error" << endl;
        exit(1);
    }


    mysql_close(r);
    return 0;
}

