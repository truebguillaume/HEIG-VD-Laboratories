#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include "generator.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "Timer.h"
#include "OpCounter.h"

using namespace std;

const unsigned int SEED = 123456;

struct Operations {
    long copyCount;
    long comparisonCount;
};

Operations testFunction(const std::function<void(std::vector<OpCounter<int>>&)> &method, size_t count, GeneratorType generatorMethod) {

    // Generate the vector with the size and repartition
    vector<OpCounter<int>> vector = generate<OpCounter<int>>(count, generatorMethod, SEED);

    // Reset the counter
    OpCounter<int>::resetCounter();

    // Call the sorting method
    method(vector);

    // Get the count into an Operations struct
    return Operations {
        OpCounter<int>::getCopyCount(),
        OpCounter<int>::getComparaisonCount()
    };
}

int main() {
    const vector<int> vectorRandom = generate<int>(100, GeneratorType::STD_DEVIATION, 12345);

    // Fetching all values for each vector
    for (GeneratorType Type: GENERATOR_TYPES) {
        ofstream out(sortName[(int) Type] + ".csv");
        out
                << "Vector size, Bubble_copy, Bubble_comp, Insertion_copy, Insertion_comp, Selection_copy, Selection_comp, StdSort_copy, StdSort_comp, StdStableSort_copy, StdStableSort_comp";
        for (size_t n: vector<size_t>{50, 100, 500, 1000, 5000, 10000}) {
            out << endl << n << ", ";

            // We still encounter the same problem as in part 2,
            // so we have to use lambdas.
            Operations result = testFunction([](auto &vec) -> void {
                bubbleSort(vec);
            }, n, Type);
            out << result.copyCount << ", " << result.comparisonCount << ", ";

            result = testFunction([](auto &vec) {
                insertionSort(vec);
            }, n, Type);
            out << result.copyCount << ", " << result.comparisonCount << ", ";

            result = testFunction([](auto &vec) -> void {
                selectionSort(vec);
            }, n, Type);
            out << result.copyCount << ", " << result.comparisonCount << ", ";

            result = testFunction([](auto &vec) -> void {
                std::sort(vec.begin(), vec.end());
            }, n, Type);
            out << result.copyCount << ", " << result.comparisonCount << ", ";

            result = testFunction([](auto &vec) -> void {
                std::stable_sort(vec.begin(), vec.end());
            }, n, Type);
            out << result.copyCount << ", " << result.comparisonCount;
        }
    }

    return EXIT_SUCCESS;
}


