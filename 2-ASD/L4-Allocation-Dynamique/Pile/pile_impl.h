#ifndef PILE_IMPL_H
#define PILE_IMPL_H

#include <stdexcept>
#include "pile.h"


/**
 * Constructeur de la pile.
 * @tparam T type des elements dans la pile
 * \param n capacite de la pile
 */
template <typename T>
Pile<T>::Pile(size_t n) :taille(0), capacite(n), data(nullptr) {
    if(n)
        data = (T *) ::operator new(n * sizeof(T));
}

/**
 * Constructeur par copie d'une pile.
 * @tparam T type des elements dans la pile
 * @param other la pile à copier
 */
template <typename T>
Pile<T>::Pile(const Pile& other) : capacite(0), taille(0), data(nullptr) {
    if (&other != nullptr) {
        data = (T*) ::operator new(other.capacite * sizeof(T));
        for (size_t i = 0; i < other.taille; i++) {
            new(&data[i]) T(other.data[i]);
        }
        capacite = other.capacite;
        taille = other.taille;
    }
}

/**
 * Destructeur de l'objet.
 * Libère la mémoire allouée en interne
 * @tparam T type des elements dans la pile
 */
template <typename T>
Pile<T>::~Pile<T>() {
    for (size_t i = 0; i < taille; i++) {
        data[i].~T();
    }
    ::operator delete(data);
    data = nullptr;
}

/**
 * Push et ajoute une element sur le dessus de la pile.
 * @tparam T type des elements dans la pile
 * @param e element à ajouter
 */
template <typename T>
void Pile<T>::push(T e) {
    if (!full()) {
        try {
            new(data + taille) T(std::move(e));
        } catch (...) {
            ::operator delete(data + taille);
            throw;
        }
        taille++;
    } else {
        throw std::out_of_range(__func__);
    }
}

/**
 * Enlève, et détruit l'élément au dessus de la pile.
 * @tparam T type des elements dans la pile
 */
template <typename T>
void Pile<T>::pop() {
    if (!empty()) {
        (data + taille - 1)->~T();
        --taille;
    } else {
        throw std::out_of_range(__func__);
    }
}

/**
 * Retourne l'élément sur le dessus de la pile.
 * @tparam T type des elements dans la pile
 * @return element de type T sur le dessus de la pile
 */
template <typename T>
const T& Pile<T>::top() const {
    return *(data + (taille - 1));
}

/**
 * Retourne `true` si la pile est vide.
 * @tparam T type des elements dans la pile
 * @return `true` si vide
 */
template <typename T>
bool Pile<T>::empty() const noexcept {
    return !taille;
}

/**
 * Retourne `true` si la pile est pleine (à capacité).
 * @tparam T type des elements dans la pile
 * @return `true` si plein (la pile est à sa capacité)
 */
template <typename T>
bool Pile<T>::full() const noexcept {
    return taille >= capacite;
}

/**
 * Échange deux piles.
 * En interne, cela échange les pointeurs vers la donnée, ainsi que les données en relation.
 * @tparam T type des elements dans la pile
 * @param param other pile à echanger
 */
template <typename T>
void Pile<T>::swap(Pile& other) noexcept {
    using std::swap;
    swap(data, other.data);
    swap(taille, other.taille);
    swap(capacite, other.capacite);
}

/**
 * Opérateur de copie, duplicant l'instance d'une pile à une autre.
 * @tparam T type des elements dans la pile
 * @param other la pile à copier
 * @return return reference sur la pile
 */
template <typename T>
Pile<T>& Pile<T>::operator=(const Pile& other) {
    if (this == &other)
        return *this;
    if (capacite < other.taille) {
        auto tmp = other;
        // nothrow
        swap(tmp);
    } else {
        for (size_t i = 0; i < other.taille; i++) {
            if (i < taille) {
                data[i] = other.data[i];
            } else {
                new(&data[i]) T(other.data[i]);
                taille = i;
            }
        }
        for (size_t i = other.taille; i < taille; i++){
            (data + i)->~T();
        }
        taille = other.taille;
    }
    return *this;
}

#endif
