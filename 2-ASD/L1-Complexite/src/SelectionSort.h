#ifndef ASD2023_L1_COMPLEXITE_TRIPARSELECTION_H
#define ASD2023_L1_COMPLEXITE_TRIPARSELECTION_H

#include <vector>

// Generic selection sort

//iterators version
template<typename T>
void selectionSort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end){
    for (auto i = begin; i != end; ++i) {
        auto iMin = i;
        for (auto j = i + 1; j < end; ++j) {
            if (*j < *iMin)
                iMin = j;
        }
        std::swap(*i, *iMin);
    }
}

//vector by ref version
template<typename T>
void selectionSort(std::vector<T>& v){
    selectionSort<T>(v.begin(), v.end());
}

#endif //ASD2023_L1_COMPLEXITE_TRIPARSELECTION_H

