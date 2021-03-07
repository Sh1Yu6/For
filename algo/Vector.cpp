
/************************************************
#
#      Filename: Vector.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-02-20 14:43:51
# Last Modified: 2021-02-20 15:50:40
#***********************************************/
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <initializer_list>
using namespace std;

template <typename Object>
class Vector{
    public:

        static constexpr int SPARE_CAPACITY = 16;
        explicit Vector(int initSize = 0): 
             theSize{initSize}, 
             theCapacity{initSize + SPARE_CAPACITY}, 
             Object{new Object[theCapacity]}{
             }

        Vector(initializer_list<Object> list):
            theSize{list.size()}, 
            theCapacity{theSize + SPARE_CAPACITY},
            objects{new Object[theCapacity]}{
                int k = 0; 
                for(auto i = list.begin(); i != list.end(); ++i){
                    objects[k++] = move(*i);
                }
            }
        

        Vector(const Vector& rhs): 
            theSize{rhs.theSize}, 
            theCapacity{rhs.theCapacity}, 
            objects{new Object[theCapacity]}{
                for(int i = 0; i < theSize; ++i){
                    objects[i] = rhs.objects[i];
                }
            }


        Vector& operator=(const Vector& rhs){
            if(&rhs == this){
                return *this;
            }
            Vector copy = rhs;
            swap(*this, copy);
            return *this;
        }

        ~Vector(){
            delete[] objects;
        }

        Vector(Vector&& rhs):
            theSize{rhs.theSize}, 
            theCapacity{rhs.theCapacity}, 
            objects{rhs.objects}{
                rhs.objects = nullptr;
                rhs.theSize = 0;
                rhs.theCapacity = 0;
            }

        Vector& operator=(Vector&& rhs){
            swap(theSize, rhs.theSize);
            swap(theCapacity, rhs.theCapacity);
            swap(objects, rhs.objects);
            return *this;
        }

        void resize(int newSize){
            if(newSize > theCapacity){
                reserve(newSize * 2);
            }
            theSize = newSize;
        }

        void reserve(int newCapacity){
            if(newCapacity < theSize){
                return;
            }

            Object* newArray = new Object[newCapacity];
            for(int i = 0; i < theSize; ++i){
                newArray[i] = move(objects[i]);
            }
            theCapacity = newCapacity;
            swap(objects, newArray);
            delete[] newArray;
        }

        Object& operator[](int index){
            return objects[index];
        }

        const Object& operator[](int index) const{
            return objects[index];
        }

        bool empty() const{
            return size() == 0;
        }

        int size() const{
            return theSize;
        }

        int capacity() const{
            return theCapacity;
        }

        void push_back(const Object& x){
            if(theSize == theCapacity){
                reserve(theCapacity * 2 + 1);
            }
            objects[theSize++] = x;
        }

        void push_back(Object&& x){
            if(theSize == theCapacity){
                reserve(theCapacity * 2 + 1);
            }
            objects[theSize++] = move(x);
        }

        void pop_back(){
            --theSize;
        }

        const Object& back() const{
            return objects[theSize - 1];
        }

        using iterator = Object*;
        using const_iterator = const Object*;

        iterator begin(){
            return &objects[0];
        }

        const_iterator begin() const{
            return &objects[0];
        }

        iterator end(){
            return &objects[size()];
        }

        const_iterator end() const{
            return &objects[size()];
        }

    private:
        int theSize;
        int theCapacity;
        Object* objects;
};

int main(){
    Vector<int> a{ 1, 2, 3, 4, 5 };
    for(auto i: a){
        cout << i << endl;
    }
    return 0;
}
