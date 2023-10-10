#ifndef TRI_PAR_BASE
#define TRI_PAR_BASE

#include <iterator>
#include <type_traits>
#include <vector>
#include <limits>
#include "some_bits.h"

using ui = unsigned int;

template<typename Iterator, typename Fn>
void tri_comptage(Iterator first, Iterator last, Iterator output_first, Fn index_fn, size_t N)
{

    // Création du vecteur de cle
    std::vector<ui> cleComptage(N+1, 0);

    // Remplissage du tableau des cles de comptage
    for(ui i = 0; (first+i) < last ; ++i){
        cleComptage.at(index_fn(*(first+i)))++;
    }

    // Réservation des plages pour chaques type de cle avec son index en première position
    std::partial_sum(cleComptage.begin(), cleComptage.end(), cleComptage.begin());
    cleComptage.insert(cleComptage.begin(),0);

    // Placement des valeurs triées dans le vecteur de sortie
    for(Iterator iterator = first ; iterator < last ; ++iterator) {
        auto offset = cleComptage.at(index_fn(*iterator))++;
        *(output_first + offset) = *iterator;
    }
}

template<typename Iterator, size_t NBITS>
void tri_par_base(Iterator first, Iterator last)
{
    using T = typename Iterator::value_type;
    static_assert(std::is_unsigned<T>::value);

    std::vector<T> vSortie(last-first);

    // Copie des valeurs du vecteur initial dans le vecteur de sortie
    std::copy(first, last, vSortie.begin());

    // Code repris de la démo de E. Ransome permettant de tester tous les bits d'un groupe de bits
    for (unsigned i = 0; i < std::numeric_limits<ui>::digits / NBITS ; ++i ) {

        // Création de la fonction pour NBITS avec i étant la position du bits à tester
        auto fn = SomeBits<unsigned long long>(NBITS, i);

        // Appel du tri comptage avec la fonction SomeBits
        tri_comptage<>(first, last, vSortie.begin(), fn, pow(2,NBITS));

        // Copie de la sortie du tri dans first
        std::copy(vSortie.begin(), vSortie.end(), first);
    }
}

#endif