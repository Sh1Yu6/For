
/************************************************
#
#      Filename: sort.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-19 14:22:09
# Last Modified: 2021-03-20 08:48:13
#***********************************************/
#include <iostream>
#include <vector>
using namespace std;

void insertSort(vector<int>& arr){
    for(int i = 1; i < arr.size(); ++i){
        int value = arr[i];
        int j = 0;
        for( j = i; j > 0 && value < arr[j-1]; --j){
                arr[j] = arr[j-1];
        }
        arr[j] = value;
    }
}

void bubbleSort(vector<int>& arr){
    for(int i = 0; i < arr.size() - 1; ++i){
        for(int j = arr.size() - 1; j > i; --j){
            if(arr[j - 1] > arr[j]){
                swap(arr[j-1], arr[j]);
            }
        }
    }
}

void selectSort(vector<int>& arr){
    for(int i = 0; i < arr.size() - 1; ++i){
        int value = arr[i];
        int index = i;
        for(int j = i; j < arr.size(); ++j){
            if(arr[j] < value){
                index = j;
            }
        }
        arr[i] = arr[index];
        arr[index] = value;
    }
}

void quickSort(vector<int>& arr, int left, int right){
    if(left >= right){
        return;
    }
    int pivot = arr[left];
    int i = left;
    int j = right;
    while(i < j){
        while(i < j && arr[j] >= pivot){
            --j;
        }
        if(i < j){
            arr[i++] = arr[j];
        }
        while(i < j && arr[i] <= pivot){
            ++i;
        }
        if(i < j){
            arr[j--] = arr[i];
        }
    }
    arr[i] = pivot;
    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}

void print(const vector<int>& arr){
    for(const auto i: arr){
            cout << i << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    vector<int> v{6, 4, 5, 3, 7, 1};
    cout << v.size() << endl;
    //insertSort(v);
    //cout << v.size() << endl;
    //print(v);
    //bubbleSort(v);
    //cout << v.size() << endl;
    //print(v);
    //selectSort(v);
    //cout << v.size() << endl;
    //print(v);
    quickSort(v, 0, v.size()-1);
    cout << v.size() << endl;
    print(v);
    return 0;
}

