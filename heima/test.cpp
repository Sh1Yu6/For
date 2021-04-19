
/************************************************
#
#      Filename: test.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-15 09:02:00
# Last Modified: 2021-04-15 09:03:47
#***********************************************/
#include <iostream>
#include <cstdio>
using namespace std;

extern "C"{
    void func(){
        printf("asdfasdfasdf");
    }
}
int main(int argc, char *argv[])
{
    func();
    return 0;
}

