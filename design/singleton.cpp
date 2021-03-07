
/************************************************
#
#      Filename: singleton.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-05 07:26:47
# Last Modified: 2021-03-05 07:35:03
#***********************************************/
#include <iostream>
using namespace std;

class Singleton{
public:
    static const Singleton* getInstance(){
        if(ptr == nullptr){
            cout << "123" << endl;
            ptr = new Singleton;
        }
        return ptr;
    }

    static void doSomeThing(){
        cout << "a" << endl;
    }
private:
    Singleton() = default;
    ~Singleton() = default;

    static Singleton* ptr;
};

Singleton* Singleton::ptr = nullptr;
int main(int argc, char *argv[])
{
    Singleton::getInstance()->doSomeThing();
    Singleton::getInstance()->doSomeThing();
    Singleton::getInstance()->doSomeThing();
    Singleton::getInstance()->doSomeThing();
    Singleton::getInstance()->doSomeThing();
    Singleton::getInstance()->doSomeThing();
    Singleton::getInstance()->doSomeThing();
    Singleton::getInstance()->doSomeThing();
    Singleton::getInstance()->doSomeThing();
    return 0;
}

