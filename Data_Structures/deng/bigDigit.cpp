
/************************************************
#
#      Filename: bigDigit.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-17 08:03:04
# Last Modified: 2021-03-17 08:15:04
#***********************************************/
#include <iostream>
#include <string>
using namespace std;

void add(string a, string b){
    int len = min(a.size(), b.size());
    int carry = 0;
    string newNum;
    while(len--){
        int numFirst = a.back()-'0';
        int numSecond = b.back()-'0';
        int add = numFirst + numSecond + carry;
        int ret = add % 10;
        carry = add / 10;
        newNum.push_back(ret);
        a.pop_back();
        b.pop_back();
    }
    while(!a.empty()){
        int num = (a.back() + carry) ;
        int add = num % 10;
        carry = num / 10;
        newNum.push_back(add);
    }
    while(!b.empty()){
        int num = (a.back() + carry) ;
        int add = num % 10;
        carry = num / 10;
        newNum.push_back(add);
    }
    for(auto i = newNum.rbegin(); i != newNum.rend(); ++i){
        cout << (int)*i;
    }
    cout << endl;
}
int main(int argc, char *argv[])
{

    string num1, num2;
    cin >> num1 >> num2;
    add(num1, num2);
    return 0;
}

