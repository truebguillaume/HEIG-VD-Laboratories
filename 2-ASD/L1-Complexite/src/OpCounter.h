//
// Created by ValentinRicard on 21.02.2023.
// Design notes:
// - It is more useful to use a generic function, that works for any value,
//    as long as they implement the required functions, for example for
//    composing measuring functions, as that would not be possible otherwise.
//

#ifndef ASD2022_L1_COMPLEXITE_OPCOUNTER_H
#define ASD2022_L1_COMPLEXITE_OPCOUNTER_H

template <typename T> class OpCounter {
private:
    T element;
    inline static long copyCount = 0;
    inline static long comparaisonCount = 0;
public:
    OpCounter(): element() {}

    OpCounter(T element): element(element) {
        ++copyCount;
    }

    OpCounter(const OpCounter<T>& ref) {
        element = ref.element;
        ++copyCount;
    }

    OpCounter &operator=(const OpCounter<T>& ref) {
        element = ref.element;
        ++copyCount;
        return *this;
    }

    friend bool operator<(const OpCounter<T>& lhs, const OpCounter<T>& rhs) {
        ++comparaisonCount;
        return lhs.element < rhs.element;
    }

    friend bool operator>(const OpCounter<T>& lhs, const OpCounter<T>& rhs) {
        ++comparaisonCount;
        return lhs.element > rhs.element;
    }

    bool operator==(const T& other) const {
        ++comparaisonCount;
        return element == other.element;
    }

    bool operator!=(const T& other) const{
        ++comparaisonCount;
        return element != other.element;
    }

    OpCounter operator++(int postIncrement) {
        return OpCounter(element++);
    }

    static long getCopyCount() {
        return copyCount;
    }

    static long getComparaisonCount() {
        return comparaisonCount;
    }

    static void resetCounter() {
        copyCount = 0;
        comparaisonCount = 0;
    }
};

#endif //ASD2022_L1_COMPLEXITE_OPCOUNTER_H
