
/************************************************
#
#      Filename: heap.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-26 07:17:05
# Last Modified: 2021-03-26 08:05:21
#***********************************************/
#include <iostream>
#include <vector>
#include <cassert>
#include "sort_test_helper.h"
using namespace std;

template<typename T>
class MaxHeap{

    public:
        MaxHeap(int capacity): data{new T[capacity + 1]},
            count{ 0 }, mCapacity{ capacity + 1 }{

        }
        ~MaxHeap(){
            delete [] data;
        }


        int size() const {
            return count;
        }

        bool isEmpty() const {
            return count == 0;
        }

        void insert(T item){
            data[count + 1] = item;
            ++count;
            shiftUp( count );
        }

        T getMax(){
            assert( count > 0 );
            T ret = data[1];
            swap( data[1], data[count] );
            --count;
            shiftDown(1);
            return ret;
        }


        void print() const{
            for(int i = 1; i <= count; ++i){
                cout << data[i] << endl;
            } 
        }

    private:
        T* data;
        int count;
        int mCapacity;

        void shiftUp( int k ){
            assert( count + 1 <= mCapacity );
            while( k > 1 &&  data[k/2] < data[k] ){
                swap( data[ k / 2 ], data[k] );
                k /= 2;
            }
        }

        void shiftDown( int k ){
            while( 2 * k <= count ){
                int j = 2 * k;
                if( j + 1 <= count && data[j+1] > data[j] ){
                    j += 1;
                }
                if( data[k] >= data[j] ){
                    break;
                }
                swap(data[k], data[j]);
                k = j;
            }
        }
};


template<typename T>
void headSort1(T* arr, int n){
    MaxHeap<T> maxHeap{n};
    for(int i = 0; i < n; ++i){
        maxHeap.insert(arr[i]);
    }
    for(int i = n - 1; i >= 0; --i){
        arr[i] = maxHeap.getMax();
    }
}


int main(int argc, char *argv[])
{
    //MaxHeap<int> h{100};
    //srand(time(nullptr));

    //for( int i = 0; i < 100; ++i ){
        //h.insert( rand() % 100 );
    //}
    //h.print();
    //cout << endl;

    //while(!h.isEmpty()){
        //cout << h.getMax() << endl;
    //}
    
    int n = 10000000;
    auto arr = SortTestHelper::generateRandomArray(n, 0, n);
    SortTestHelper::testSort("Heap Sort", headSort1, arr, n);

    delete [] arr;
    return 0;
}

