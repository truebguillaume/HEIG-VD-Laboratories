#ifndef ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
#define ASD_LABS_2021_AVLNODEIMPLEMENTATION_H

#include "avlNode.h"
#include "parser.h"
#include <cmath>

namespace avl {

    template<typename Key>
    void insert_in_subtree(Node<Key>*&r, Key const &k) {
        if (r == nullptr) {
            r = new Node<Key>{k, Node<Key>::NO_CHILD, 1};
        } else if (k == r->key) {
            return;
        } else {
            Side s = k < r->key ? LEFT : RIGHT;
            insert_in_subtree(r->children[s], k);
        }
        r->height = calc_height(r);
    }

    template<typename Key>
    int calc_height(Node<Key>*&r) {
        if (r == nullptr)
            return 0;
        else
            return 1 + std::max(calc_height(r->left()), calc_height(r->right()));
    };

    template<typename Key>
    std::ostream &show_indented(Node<Key>* r,
                                std::ostream &out,
                                std::string before,
                                bool isright) {
        out << before;
        if (not r) {
            out << ".\n";
        } else {
            if (not before.empty()) {
                before[before.size() - 2] = ' ';
                if (isright) {
                    before[before.size() - 3] = ' ';
                }
            }
            out << r->key << std::endl;
            if (r->children != Node<Key>::NO_CHILD) {
                for (Side s: {LEFT, RIGHT}) {
                    show_indented(r->children[s], out, before + "|_ ", s);
                }
            }
        }
        return out;
    }

    template<typename Key>
    std::ostream &operator<<(std::ostream &out, const Node<Key>* node) {
        if (not node) {
            out << ".";
            return out;
        }

        out << node->key;
        // On affiche la leaf node:
        out << '(';
        for (Side s: {LEFT, RIGHT}) {
            if (s) {
                out << ",";
            }
            out << node->children[s];
        }
        out << ")";

        return out;
    }

    template<typename Key>
    Node<Key>* parse_node(std::istream &in) {
        if (in.peek() == '.') {
            in.get();

            return nullptr;
        }
        // Not an empty, so we allocate a new element:
        Key key;
        in >> key;
        auto node = new Node<Key>{key, Node<Key>::NO_CHILD, 1};

        parser::expect(in, '(');
        // Now, let's hope we get everything in:
        for (Side s: {LEFT, RIGHT}) {
            if (s) {
                parser::expect(in, ',');
            }
            node->children[s] = parse_node<Key>(in);
        }
        parser::expect(in, ')');

        return node;
    }


    template<typename Key>
    void free_node(Node<Key> *&r) {
        if (r == nullptr) {
            return;
        }
        free_node(r->left());
        free_node(r->right());

        delete &*r;
    }

    template<typename Key>
    Node<Key>*& findKeyReference(Node<Key> *&r, const Key &k) {
        if(r->key == k)
            return r;
        else if(k < r->key)
            return findKeyReference(r->left(), k);
        else if(k > r->key)
            return findKeyReference(r->right(), k);
    }

    template<typename Key>
    Node<Key>* findKey(Node<Key> * const &r, const Key &k) {
        if (r == nullptr)
            return nullptr;
        else if(r->key == k)
            return r;
        else if(k < r->key)
            return findKey(r->left(), k);
        else if(k > r->key)
            return findKey(r->right(), k);
        else
            return nullptr;
    }

    template<typename Key>
    Node<Key>* findParent(Node<Key> *&r, const Key &k) {
        if(r->key == k)
            return nullptr;
        Node<Key>* child = k < r->key ? r->left() : r->right();
        if(child->key == k)
            return r;
        else if(child->key != k)
            return findParent(child, k);
        else
            return nullptr;
    }

    template<typename Key>
    Node<Key>* clone(const Node<Key>* other) {
        if (other == nullptr) {
            return nullptr;
        }

        // Alloue un nouvel élément
        auto cloned = new Node<Key>{other->key, Node<Key>::NO_CHILD, other->height};

        for (Side s: {LEFT, RIGHT}) {
            cloned->children[s] = clone(other->children[s]);
        }

        return cloned;
    }
}

#endif //ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
