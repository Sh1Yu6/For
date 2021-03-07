
/************************************************
#
#      Filename: test2.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-02-16 17:12:11
# Last Modified: 2021-02-16 17:20:25
#***********************************************/
#include <iostream>
#include <random>
#include <functional>
using namespace std;
int main(int argc, char *argv[])
{
    auto die = bind(uniform_int_distribution<>{1, 6}, default_random_engine{});
    for(int i = 0; i < 10; ++i){
        cout << die() << endl;
    }
    return 0;
}

