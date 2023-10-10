#ifndef TRI_RAPIDE
#define TRI_RAPIDE

#include <algorithm>
#include <random>
#include <vector>



template<typename Iterator>
Iterator partition(Iterator first, Iterator last) {


    static std::random_device randomDevice;
    static std::mt19937 generateurAleatore(randomDevice());

    // Choix du pivot aleatoire
    std::uniform_int_distribution<> distribution(0, std::distance(first, last) - 1);
    int random = distribution(generateurAleatore);
    auto pivot = *(first + random);
    std::swap(*first, *(first + random));

    // Indices
    Iterator i = first + 1;
    Iterator j = last - 1;

    // Creation de la partition
    while (i <= j) {

        while (i <= j && *i <= pivot) {
            ++i;
        }

        while (i <= j && *j > pivot) {
            --j;
        }

        if (i < j) {
            std::swap(*i, *j);
        }
    }
    std::swap(*first, *(i - 1));


    // Retourne la position du pivot
    return i - 1;
}

//Implémentation de la fonction tri
template<typename Iterateur>
void tri_rapide(Iterateur first, Iterateur last) {

    // Version semi recursive

    while (first < last) {

        auto i = partition(first, last);

        if (i - first < last - i) {
            tri_rapide(first, i);
            first = i + 1;
        } else {
            tri_rapide(i + 1, last);
            last = i;
        }
    }

}

#endif