
/************************************************
#
#      Filename: List.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-02-20 15:50:43
# Last Modified: 2021-02-20 16:05:06
#***********************************************/
#include <iostream>
using namespace std;

template<typename Object>
class List{
public:
    class const_iterator{

    };

    class iterator: public const_iterator{

    };
    
private:
    struct Node{

    };

public:
    List(){

    }

    List(const List& rhs){

    }

    List& operator=(const List& rhs){

    }

    List(List&& rhs){

    }

    List& operator=(List&& rhs){

    }

    ~List(){

    }

    iterator begin(){
        return head->next;
    }
};

int main(int argc, char *argv[])
{
    return 0;
}

