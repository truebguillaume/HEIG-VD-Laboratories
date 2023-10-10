#ifndef ASD2022_L1_COMPLEXITE_INSERTIONSORT_H
#define ASD2022_L1_COMPLEXITE_INSERTIONSORT_H

#include <vector>
#include <iostream>

//Generic InsertionSort fonction

//iterators version
template<typename T>
void insertionSort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end) {
    for (auto i = begin + 1; i != end; ++i) {
        for (auto j = i; j != begin && *(j-1) > *(j); --j) {
            std::swap(*j, *(j-1));
        }
    }
}

//vector by ref version
template<typename T>
void insertionSort(std::vector<T>& v) {
    insertionSort<T>(v.begin(), v.end());
}

#endif //ASD2022_L1_COMPLEXITE_INSERTIONSORT_H
