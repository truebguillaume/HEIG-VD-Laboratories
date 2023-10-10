//
// Created by ValentinRicard on 23.02.2023.
//

#ifndef ASD2022_L1_COMPLEXITE_GENERATOR_H
#define ASD2022_L1_COMPLEXITE_GENERATOR_H

#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <array>
#include <algorithm>
#include <stdexcept>

template <typename T> std::vector<T> genereTrie(size_t size) {
    std::vector<T> result;
    for (size_t idx = 0; idx < size; ++idx) {
        // As we require a size_t constructor for the nearlySorted algorithm, we can use it here too
        result.push_back(T(idx));
    }

    return result;
}

template <typename T> std::vector<T> genereInverse(size_t size) {
    std::vector<T> result;
    for (size_t idx = size; idx > 0; --idx) {
        // As we require a size_t constructor for the nearlySorted algorithm, we can use it here too
        result.push_back(T(idx));
    }
    return result;
}

template <typename T> std::vector<T> genereMelange(size_t size, unsigned int seed){
    std::vector<T> result = genereTrie<T>(size);

    // We generate the random engine
    std::default_random_engine random(seed);

    std::shuffle(result.begin(), result.end(), random);

    return result;
}



int genereDistributionNormale(int mean, int deviation, std::default_random_engine &engine) {
    // Get the distribution. To get a nearly sorted array, we use a deviation of 1 + n/20
    std::normal_distribution<float> distribution((float) mean, (float) deviation);
    return (int) distribution(engine);
}

template<typename T> std::vector<T> generePresqueMelange(size_t size, unsigned int seed) {
    std::vector<T> result;
    // We generate the random engine
    std::default_random_engine random(seed);
    for (size_t idx = 0; idx < size; ++idx) {
        size_t deviation = 1 + size / 20;
        result.push_back(T((size_t) std::max(genereDistributionNormale((int) idx, (int) deviation, random), 0)));
    }

    return result;
}

std::string nomsGenerateurs[] = {"sorted", "reversed", "random", "std-dev"};

enum class GeneratorType {
            SORTED,
            REVERSED,
            RANDOM,
            STD_DEVIATION
        };

constexpr std::array<GeneratorType, 4> GENERATOR_TYPES = {
            GeneratorType::SORTED,
            GeneratorType::REVERSED,
            GeneratorType::RANDOM,
            GeneratorType::STD_DEVIATION
        };

std::string getNomGenerateur(GeneratorType type) {
    return nomsGenerateurs[(size_t) type];
}


template <typename T> std::vector<T> genererVecteur(size_t size, GeneratorType type, unsigned int seed) {
    switch (type) {
        case GeneratorType::SORTED:
            return genereTrie<T>(size);
        case GeneratorType::REVERSED:
            return genereInverse<T>(size);
        case GeneratorType::RANDOM:
            return genereMelange<T>(size, seed);
        case GeneratorType::STD_DEVIATION:
            return generePresqueMelange<T>(size, seed);
        default:
            // Wreck things
            throw std::logic_error("Unknown GeneratorType variant!");
    }
}
#endif //ASD2022_L1_COMPLEXITE_GENERATOR_H
