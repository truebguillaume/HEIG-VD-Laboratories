#include <iostream>
#include <vector>
#include <fstream>
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "Timer.h"

using namespace std;

template <typename T>
void vectorOutput(vector<T> v);

int main(){

    cout << "Test of the algorithm we wrote :" << endl << endl;

    //Vector for the tests
    const vector<int> vConst = {1,-23,43,23,5,73,-32,56,2,24,0,76,-54,8,108,-3,237,42,-87};
    vector<int> v = vConst;

    //BubbleSort test
    cout << "BubbleSort test : " << endl << "Unsorted vector : ";
    vectorOutput(v);
    bubbleSort<int>(v);
    cout << "Sorted vector   : ";
    vectorOutput(v);
    cout << boolalpha << "Is sorted       : "
    << is_sorted(v.begin(), v.end()) << endl;
    v = vConst;
    cout << endl;

    //SelectionSort test
    cout << "SelectionSort test : " << endl << "Unsorted vector : ";
    vectorOutput(v);
    selectionSort<int>(v);
    cout << "Sorted vector   : ";
    vectorOutput(v);
    cout << boolalpha << "Is sorted       : "
    << is_sorted(v.begin(), v.end()) << endl;
    v = vConst;
    cout << endl;

    //InsertionSort test
    cout << "InsertionSort test : " << endl << "Unsorted vector : ";
    vectorOutput(v);
    insertionSort<int>(v);
    cout << "Sorted vector   : ";
    vectorOutput(v);
    cout << boolalpha << "Is sorted       : "
    << is_sorted(v.begin(), v.end()) << endl;
    v = vConst;
    cout << endl;

    return EXIT_SUCCESS;
}

template <typename T>
void vectorOutput(vector<T> v){
    cout << "[";
    for(size_t i = 0 ; i < v.size() ; ++i){
        cout << v[i];
        if(i != v.size() - 1){
            cout << ",";
        }
    }

    cout << "]" << endl;
}


