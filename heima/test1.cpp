
/************************************************
#
#      Filename: test1.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-02-16 16:23:02
# Last Modified: 2021-02-16 16:28:27
#***********************************************/
#include <iostream>
#include <thread>
using namespace std;

struct A{
    void operator()(){
        for(int i = 0; i < 10; ++i)
            cout << "aaaaaaaaaaaa" << endl;
    }
};
struct B{
    void operator()(){
        for(int i = 0; i < 10; ++i)
            cout << "bbbbbbbbbbb" << endl;
    }
};

int main(int argc, char *argv[])
{
    thread t1{A()};
    thread t2{B()};

    t1.join();
    t2.join();
    return 0;
}

