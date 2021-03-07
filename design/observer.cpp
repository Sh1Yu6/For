
#ifndef OBSERVER_H_
#define OBSERVER_H_
/************************************************
#
#      Filename: observer.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-05 07:36:35
# Last Modified: 2021-03-05 08:14:07
#***********************************************/
#include <iostream>
#include <list>
#include <string>
using namespace std;

class Observer{
public:
    Observer() = default;
    virtual ~Observer(){

    }

    virtual void update(void* pArg) = 0;
};

class UserA: public Observer{
    virtual void update( void* pArg ){
        cout << "Aaaaaaaa" << (char*)pArg << endl;
    }
};

class UserB: public Observer{
    virtual void update( void* pArg ){
        cout << "Bbbbbbbb" << (char*)pArg<< endl;
    }
};

///////////////-----------------------------------------------------
//
class Oberverable{
public:
    Oberverable() = default;
    virtual ~Oberverable() = default;

    void attach(Observer* pOb){
        if(pOb == nullptr){
            return;
        }

        for(const auto& i: obs){
            if(i == pOb){
                return;
            }
        }

        obs.push_back(pOb);

    }

    void detach(Observer* pOb){
        if(pOb == nullptr || obs.empty()){
            return;
        }
        obs.remove(pOb);
    }

    virtual void getSomeNews(string str){
        setChange(str);
    }

protected:
    void setChange(string str){
        change = true;
        notify(reinterpret_cast<void*>(const_cast<char*>(str.c_str())));
    }
private:
    void notify(void* pArg){
        if(change == false){
            return;
        }
        for(const auto& i: obs){
            i->update(pArg);
        }
        change = false;
    }
private:
    list<Observer*> obs;
    bool change = false;
};

int main(int argc, char *argv[])
{
    UserA a;
    UserB b;

    Oberverable c;
    c.getSomeNews("111111111111111");
    c.attach(&a);
    c.attach(&b);
    c.getSomeNews("222222222222222");
    c.detach(&a);
    c.getSomeNews("3333333333333333333");
    return 0;
}
#endif
