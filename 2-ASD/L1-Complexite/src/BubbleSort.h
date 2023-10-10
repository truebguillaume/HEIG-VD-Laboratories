#ifndef ASD2022_L1_COMPLEXITE_TRIPARBULLE_H
#define ASD2022_L1_COMPLEXITE_TRIPARBULLE_H

#include <vector>
#include <iostream>

//Generic BubbleSort fonction

//iterators version
template<typename T>
void bubbleSort(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last) {
    int n = (int) std::distance(first, last);

    for (auto j = n - 1; j >= 0; j--) {
        bool swapped = false;
        auto prev = first;
        for (auto curr = std::next(first); curr != std::next(first, j + 1); ++curr, ++prev) {
            if (*prev > *curr) {
                std::swap(*prev, *curr);
                swapped = true;
            }
        }
        if (!swapped) {
            // If no swaps occurred in this iteration, the array is already sorted
            break;
        }
    }
}
//vector by ref version
template<typename T>
void bubbleSort(std::vector<T>& v) {
    bubbleSort<T>(v.begin(), v.end());
}

#endif //ASD2022_L1_COMPLEXITE_TRIPARBULLE_H

