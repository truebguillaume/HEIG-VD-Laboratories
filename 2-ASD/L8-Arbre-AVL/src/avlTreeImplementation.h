#ifndef ASD_2021_AVL_IMPL_H
#define ASD_2021_AVL_IMPL_H

#include <utility>
#include <algorithm>

template<typename Key>
avlTree<Key>::avlTree() : root(nullptr) {
}

template<typename Key>
avlTree<Key>::~avlTree() {
    free_node(this->root);
}

template<typename Key>
int balancing(avl::Node<Key>*&r) {
    if (r == nullptr)
        return 0;
    else
        return (calc_height(r->left()) - calc_height(r->right()));
}

template<typename Key>
void left_rotation(avl::Node<Key>*&r) {
    avl::Node<Key>* temp = r->right();
    r->right() = temp->left();
    temp->left() = r;
    r = temp;
}

template<typename Key>
void right_rotation(avl::Node<Key>*&r) {
    avl::Node<Key>* temp = r->left();
    r->left() = temp->right();
    temp->right() = r;
    r = temp;
}

template<typename Key>
void make_balancing(avl::Node<Key>*&r) {
    if (r == nullptr)
        return;
    if (balancing(r) < -1) {
        if (balancing(r->right()) > 0)
            right_rotation(r->right());
        left_rotation(r);
    } else if (balancing(r) > 1) {
        if (balancing(r->left()) < 0)
            left_rotation(r->left());
        right_rotation(r);
    }
}

template<typename Key>
void avlTree<Key>::insert(Key const &k) {
    avl::insert_in_subtree(root, k);
    make_balancing<Key>(*&root);
}

template<typename Key>
std::ostream &avlTree<Key>::show_indented(std::ostream &out) const {
    return avl::show_indented(root, out);
}

template<typename Key>
std::ostream &operator<<(std::ostream &out, avlTree<Key> const &tree) {
    out << tree.root;
    return out;
}

template<typename Key>
std::istream &operator>>(std::istream &in, avlTree<Key> &tree) {
    tree.root = avl::parse_node<Key>(in);
    return in;
}

//Methode qui retourne la clé la plus petite
template<typename Key>
Key const &avlTree<Key>::min() const {

    avl::Node<Key>* tampon = this->root;

    while (tampon->left() != nullptr) {
        tampon = tampon->left();
    }

    return tampon->key;

}

//Methode qui retourne la clé la plus grande
template<typename Key>
Key const &avlTree<Key>::max() const {

    avl::Node<Key>* tampon = this->root;

    while (tampon->right() != nullptr) {
        tampon = tampon->right();
    }

    return tampon->key;

}

//Methode qui retourne un pointeur sur le plus petit element d'un sous-arbre
template<typename Key>
avl::Node<Key>* minSubtree(avl::Node<Key>*&r) {
    if (r->left() != nullptr) {
        // We need to keep the reference, so we have to do it twice
        return minSubtree(r->left());
    } else {
        avl::Node<Key>* temp = r;
        r = r->right();
        return temp;
    }
}

//Methode qui supprime le nœud avec la plus petite clé
template<typename Key>
void avlTree<Key>::erase_min() {

    avl::Node<Key>* racine = this->root;
    avl::Node<Key>* tampon = nullptr;

    //Recherche du min
    while (racine->left() != nullptr) {
        tampon = racine;
        racine = racine->left();
    }

    if (tampon == nullptr) {
        this->root = nullptr;
        delete racine;
    } else if (racine->right() == nullptr && racine->left() == nullptr) {
        //Si le min n'a pas d'enfants
        tampon->left() = nullptr;
        delete racine;
    } else if (racine->right() != nullptr && racine->left() == nullptr) {
        //Si le min a un enfant à droite (gauche et deux pas possible)
        tampon->left() = racine->right();
        delete racine;
    }

    make_balancing(this->root);
}

//Methode qui supprime le nœud avec la plus grande clé
template<typename Key>
void avlTree<Key>::erase_max() {

    avl::Node<Key>* racine = this->root;
    avl::Node<Key>* tampon = nullptr;


    //Recherche du max
    while (racine->right() != nullptr) {
        tampon = racine;
        racine = racine->right();
    }

    //Si le max n'a pas d'enfants
    if (tampon == nullptr) {
        this->root = nullptr;
        delete racine;
    } else if (racine->right() == nullptr && racine->left() == nullptr) {
        tampon->right() = nullptr;
        delete racine;
    } else if (racine->right() != nullptr && racine->left() == nullptr) {
        //Si le max a un enfant à gauche (droite et deux pas possible)
        tampon->right() = racine->left();
        delete racine;
    }

    make_balancing(this->root);
}

template<typename Key>
void eraseKey(avl::Node<Key>*&r, const Key &k) {
    if (r == nullptr)
        return;
    else if (k < r->key)
        eraseKey(r->left(), k);
    else if (k > r->key)
        eraseKey(r->right(), k);
    else {
        if (r->left() == nullptr) {
            r = r->right();
        } else if (r->right() == nullptr) {
            r = r->left();
        } else {
            avl::Node<Key>* minTemp = minSubtree(r->right());
            minTemp->right() = r->right();
            minTemp->left() = r->left();
            r = minTemp;
        }
    }
}

template<typename Key>
void avlTree<Key>::erase(const Key &k) noexcept {
    eraseKey(this->root, k);
    make_balancing(this->root);
}


template<typename Key>
avlTree<Key>::avlTree(const avlTree &other) {
    // Clone les nodes de l'autre:
    this->root = avl::clone(other.root);
}

template<typename Key>
avlTree<Key> &avlTree<Key>::operator=(const avlTree<Key> &other) {
    if (this == &other) {
        return *this;
    }
    // Copier les nodes:
    this->root = avl::clone(other.root);

    return *this;
}

template<typename Key>
bool avlTree<Key>::contains(const Key &k) const noexcept {
    auto value = avl::findKey<Key>(this->root, k);
    return value != nullptr;
}

template<typename Key>
unsigned char avlTree<Key>::height() const noexcept {
    if (this->root == nullptr) {
        return 0;
    }
    return this->root->height;
}

#endif //ASD_2021_AVL_IMPL_H
