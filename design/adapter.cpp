
/************************************************
#
#      Filename: adapter.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-05 08:31:40
# Last Modified: 2021-03-05 08:54:31
#***********************************************/
#include <iostream>
#include <string>
using namespace std;

class LegacyRecangle{
public:
    LegacyRecangle(double x1, double y1, double x2, double y2){
        xx1 = x1;
        xx2 = x2;
        yy1 = y1;
        yy2 = y2;
    }

    void legacyDraw(){
        cout << "AAA" << xx1 << " " << xx2 << " " << yy1 << " " << yy2 << endl;
    }
private:
    double xx1;
    double xx2;
    double yy1;
    double yy2;
};

class Recangle{
public:
    virtual void draw(string str) = 0;
};

class RecangleAdapter: public Recangle, public LegacyRecangle{
public:
};

int main(int argc, char *argv[])
{
    return 0;
}

