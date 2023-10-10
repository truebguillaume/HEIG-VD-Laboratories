#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include "generator.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "Timer.h"

using namespace std;

const unsigned int SEED = 123456;

/**
 * Method to test the sorting methods for each vector size and repartition.
 * @param method the sorting method
 * @param count the size of the vector
 * @param generatorMethod the repartition of the vector
 * @return the time taken by the sorting method
 */
int testFunction(const std::function<void(std::vector<int>&)> &method, size_t count, GeneratorType generatorMethod) {

    // Generate the vector with the size and repartition
    vector<int> vector = generate<int>(count, generatorMethod, SEED);

    // Create the timer object
    Timer timer{};

    timer.start();
    // Call the sorting method
    method(vector);

    timer.stop();

    // Return the time taken by the sorting method
    return timer.getElapsedTime();
}


int main(){

    // Fetching all values for each vector
    for(GeneratorType Type : GENERATOR_TYPES)
    {
        // Naming the .csv file by the name of the sorting method of the vectors
        ofstream out(sortName[(int) Type] + ".csv");
        // Labeling the columns
        out << "Vector size, Bubble, Insertion, Selection, StdSort, StdStableSort";

        // Testing each sorting method for each vector size
        for(size_t n : vector<size_t>{50, 100, 500, 1000, 5000, 10000})
        {
            out << endl << n << ", ";
            // We are using a lambda function to call the sorting methods
            // due to the fact that the compiler cannot deduce the parameters
            // the function accepts.
            out << testFunction([](auto &vec) -> void {
                bubbleSort(vec);
            }, n, Type) << ", ";
            out << testFunction([](auto &vec) -> void {
                insertionSort(vec);
            }, n, Type) << ", ";
            out << testFunction([](auto &vec) -> void {
                selectionSort(vec);
            }, n, Type) << ", ";
            out << testFunction([](auto &vec) -> void {
                std::sort(vec.begin(), vec.end());
            }, n, Type) << ", ";
            out << testFunction([](auto &vec) -> void {
                std::stable_sort(vec.begin(), vec.end());
            }, n, Type);
        }
    }

    return EXIT_SUCCESS;
}


