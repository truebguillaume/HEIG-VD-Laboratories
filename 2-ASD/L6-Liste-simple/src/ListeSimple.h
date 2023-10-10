#ifndef LISTE_H
#define LISTE_H

#include "LSIterator.h"
#include <utility> // std::swap;

template <typename T>
class ListeSimple {
public:
    using value_type = T;
    using reference = T &;
    using const_reference = T const &;

private:
    struct Maillon {
        value_type valeur;
        Maillon* suivant;
    };

    Maillon avant_premier;

public:
    using iterator = LSIterator<value_type>;
    friend iterator;

    using const_iterator = LSConstIterator<value_type>;
    friend const_iterator;

    const_iterator cbegin() const noexcept { return const_iterator(avant_premier.suivant); }
    iterator begin() noexcept { return iterator(avant_premier.suivant); }
    const_iterator begin() const noexcept { return cbegin(); }

    ListeSimple() : avant_premier{value_type{}, nullptr} {
    }

    // A compléter pour fournir ...
    //
    // end, cend, before_begin, cbefore_begin, empty, front
    // insert_after, erase_after, splice_after, push_front, pop_front,
    // swap, sort, ainsi que constructeur, opérateur d'affectation et destructeur

};

#endif //LISTE_H
