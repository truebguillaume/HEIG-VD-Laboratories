#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <cstddef> // std::size_t
#include <ostream> // std::ostream
// Ajoutez si nécessaire d'autres inclusions de librairies
#include <utility> // std::move
#include <memory> // std::destroy_at

template<class T>
class ArrayDeque {
public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T*;
    using size_type = std::size_t;

    /**
     * Constructeur de base pour la classe ArrayDeque
     * @param _capacite Capacité demandée pour le buffer
     */
    ArrayDeque(size_type _capacite = 0) : debut(0),
                                          taille(0),
                                          capacite(_capacite),
                                          buffer(nullptr) {
        if (capacite)
            buffer = reinterpret_cast<pointer> (
                    ::operator new(capacite * sizeof(value_type)));
    }

    // Placez ici les méthodes publiques nécessaires pour passer le codecheck
    using diff_type = std::ptrdiff_t;

    /**
     * Constructeur par copie
     * @param other Objet ArrayDeque à copier
     */
    ArrayDeque(const ArrayDeque<T> &other) : ArrayDeque(other.capacite) {
        // Si la capacité est différente de 0 on va copier les valeurs dans le buffer
        if (capacite) {
            for (; taille < other.taille;) {
                new(buffer + taille) value_type(other[taille]);
                ++taille;
            }
        }
    }

    /**
     * Opérateur d'affectation
     * @param other Objet ArrayDeque à affecter
     * @return un pointeur sur le nouvel objet crée
     */
    ArrayDeque<T> &operator=(const ArrayDeque<T> &other) {
        ArrayDeque<T> newElement(other);

        swap(newElement);

        // newElement sera drop, donc les anciens éléments seront correctement supprimés
        return *this;
    }

    /**
     * Destructeur permettant de détruire tous les éléments du buffer
     */
    ~ArrayDeque<T>() {
        for (int i = 0; i < taille; ++i) {
            std::destroy_at(pointeurVers(i));
        }
        ::operator delete(buffer);
    }

    /**
     * Retourne la taille du buffer
     * @return la taille du buffer
     */
    size_type size() const {
        return taille;
    }

    /**
     * Retourne la capacitée du buffer
     * @return la capacitée du buffer
     */
    size_type capacity() const {
        return capacite;
    }

    /**
     * Retourne le premier element du buffer
     * @return le premier element du buffer
     */
    const_reference front() const {
        return (*this)[0];
    }

    /**
     * Retourne le premier element du buffer
     * @return le premier element du buffer
     */
    reference front() {
        return (*this)[0];
    }

    /**
     * Retourne le dernier element du buffer
     * @return retourne le dernier element du buffer
     */
    const_reference back() const {
        return (*this)[taille - 1];
    }

    /**
     * Retourne le dernier element du buffer
     * @return retourne le dernier element du buffer
     */
    reference back() {
        return (*this)[taille - 1];
    }

    /**
     * Ajoute val en tete du buffer
     * @param val la valeur à ajouter au début du buffer
     */
    void push_front(const value_type &val) {
        agrandirSiPlein();

        if (taille < capacite) {
            new(pointeurVers(-1)) value_type(val);
            // SAFETY: comme les changements d'éléments sont effectués après l'initialisation
            // (qui peut être lancée), le tableau est sûr.
            debut = index(-1);
            ++taille;
        }
    }

    /**
     * Ajoute val en queue du buffer
     * @param val la valeur à ajouter à la fin du buffer
     */
    void push_back(const value_type &val) {
        agrandirSiPlein();

        if (taille < capacite) {
            new(pointeurVers(taille)) value_type(val);
            ++taille;
        }
    }

    /**
     * Supprime l'element en tete
     */
    void pop_front() {
        if (taille > 0) {
            std::destroy_at(pointeurVers(0));
            debut = index(1);
            --taille;
        }
    }

    /**
     * Supprime l'element en queue
     */
    void pop_back() {
        // delete le dernier element
        // SAFETY : dans le cas où le destructeur lève une exception,
        // l'élément est considéré comme supprimé.
        if (taille > 0) {
            std::destroy_at(pointeurVers(--taille));
        }
    }

    /**
     * Savoir si le buffer est vide ou non
     * @return un boolean
     */
    bool empty() const {
        return taille == 0;
    }

    /**
     * Swap deux elements
     * @param other
     */
    void swap(ArrayDeque<value_type> &other) {
        using std::swap;
        swap(capacite, other.capacite);
        swap(debut, other.debut);
        swap(taille, other.taille);
        swap(buffer, other.buffer);
    }

    /**
     * Récupère une référence vers d'élément à l'index souhaité
     * @param idx L'index de l'élément souhaité
     * @return Une référence de l'élément souhaité
     *
     * @note Si l'index > taille, le comportement est indéterminé.
     */
    reference operator[](size_type idx) {
        return buffer[index(idx)];
    }

    /**
     * Récupère une référence constante vers d'élément à l'index souhaité
     * @param idx L'index de l'élément souhaité
     * @return Une référence constante de l'élément souhaité
     *
     * @note Si l'index > taille, le comportement est indéterminé.
     */
    const_reference operator[](size_type idx) const {
        return buffer[index(idx)];
    }

    /**
     * Retourne une référence constante sur un élément du buffer
     * @param index de l'élément dans le buffer
     * @return une référence constante sur l'élément index
     *
     * @note Si l'index > taille, la fonction retourne une erreur.
     */
    const_reference at(size_type index) const {
        if (index > taille) {
            throw std::out_of_range("Index " + std::to_string(index) + " is out of bounds.");
        }
        return (*this)[index];
    }

    /**
     * Ajuste la capacité à la taille
     */
    void shrink_to_fit() {
        // Create a new deque
        changerTaille(taille);
    }

private:
    pointer buffer;
    size_type capacite;
    size_type debut;
    size_type taille;

    // Placez ici les méthodes privées qui permettent de rendre votre code plus clair
    /**
     * Convertit l'index logique en index physique
     * @param index Index logique de l'élément
     * @return L'index physique de l'élément
     */
    size_type index(diff_type index) const {
        return wrap(debut + index, capacite);
    }

    /**
     * Fonction interne permettant de boucler en toute sécurité sur les éléments
     * @param value La valeur à convertir
     * @param maxWrap La valeur maximale (exclue)
     * @return Le modulo de l'élément
     */
    size_type wrap(diff_type value, size_t maxWrap) const {
        if (maxWrap == 0) {
            return 0;
        }
        // Ajouter capacité permet de gérer le cas ou value =
        return ((unsigned)value + maxWrap) % (maxWrap);
    }

    /**
     * Retourne un pointeur sur l'élément souhaité du buffer
     * @param index de la valeur souhaitée
     * @return pointeur sur l'élément en position index du buffer
     */
    pointer pointeurVers(diff_type index) {
        return &(*this)[index];
    }

    /**
     * Agrandit le buffer si la totalité du tableau est remplie
     */
    void agrandirSiPlein() {
        if (taille == capacite) {
            size_type newCapacite = capacite != 0 ? capacite * 2 : 1;

            changerTaille(newCapacite);
        }
    }

    /**
     * Change la taille de la deque
     * @param newSize nouvelle taille
     */
    void changerTaille(size_type newSize) {
        ArrayDeque<T> replacement(newSize);

        // Copier tous les éléments
        for (size_type i = 0; i < taille; ++i) {
            replacement.push_back(at(i));
        }

        // remplacer le buffer
        swap(replacement);
    }
};

template<typename T>
inline
std::ostream &operator<<(std::ostream &s,
                         const ArrayDeque<T> &v) {
    s << "(" << v.size() << "/" << v.capacity() << ") : ";
    if (not v.empty())
        s << v.front() << " -> " << v.back() << " : ";
    s << "[";
    for (int i = 0; i < v.size(); ++i) {
        s << v[i];
        if (i != v.size() - 1)
            s << ", ";
    }
    s << "]";
    return s;
}

#endif /* ArrayDeque_h */