
/************************************************
#
#      Filename: dir.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-12 16:10:46
# Last Modified: 2021-04-12 16:26:10
#***********************************************/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
    
    DIR* pDir = opendir("./");
    struct dirent* p = nullptr;
    while( ( p = readdir(pDir) ) ){
        if(string(p->d_name) == "." || string(p->d_name) == ".." ){
            continue;
        }
        if(strcmp(p->d_name, ".")|| strcmp(p->d_name, "..")){
            continue;
        }
        cout << p->d_name << " ";
        switch( p->d_type ){
            case DT_REG:
                cout << "REG" << endl;
                break;
            case DT_DIR:
                cout << "DIR" << endl;
                break;
            case DT_LNK:
                cout << "LNK" << endl;
                break;
        }
    }
    closedir(pDir);
    return 0;
}

