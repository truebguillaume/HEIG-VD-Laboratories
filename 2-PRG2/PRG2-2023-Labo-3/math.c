//---------------------------------------------------------
// Labo           : LABO3 - Bateaux
// Classe         : PRG2
// Fichier        : math.c
// Auteur(s)      : Valentin Ricard, Gwendal Piemontesi,
//                  Guillaume Trueb
// But            : Implémente une série d'utilitaires pour le calcul de statistiques "génériques"
// Remarque(s)    : Les fonctions de cette classe sont "génériques", s'inspirant de la fonction
//                  qsort de la librairie standard.
//                  La complexité supplémentaire est justifiable par sa flexibilité et
//                  modularité supplémentaire.
//---------------------------------------------------------

#include "math.h"
#include <math.h>

// Macro interne, permettant de faciliter la récupération d'élément dans un array "générique" (void*)
// NOTE: Le char* permet de faire l'arithmétique sur tous les compilateurs.
#define getAt(tableau, index, tailleElement) ((void*) (((char*) tableau) + (((size_t) (index)) * (tailleElement))))

unsigned int somme(const void* element, size_t taille, size_t tailleElement, int (* versValeur)(const void*)) {
    int total = 0;
    for (size_t i = 0; i < taille; ++i) {
        total += versValeur(getAt(element, i, tailleElement));
    }

    return total;
}

double moyenne(const void* element, size_t taille, size_t tailleElement, int (* versValeur)(const void*)) {
    return ((float) somme(element, taille, tailleElement, versValeur)) / (float) taille;
}

double mediane(const void* valeurs, size_t taille, size_t tailleElement, int (* versValeur)(const void* pointeur)) {
    if (taille % 2 == 0) {
        return (double) (versValeur(getAt(valeurs, taille / 2, tailleElement)) +
                         versValeur(getAt(valeurs, taille / 2 + 1, tailleElement))) / 2.0f;
    } else {
        return (double) versValeur(getAt(valeurs, taille / 2, tailleElement));
    }
}

double ecartType(const void* valeurs, size_t taille, size_t tailleElement, int (* versValeur)(const void* pointeur)) {
    // On récupère la moyenne:
    double moyenneValeurs = moyenne(valeurs, taille, tailleElement, versValeur);
    double differenceCarree = 0.0f;
    for (size_t i = 0; i < taille; ++i) {
        double ecart = (float) versValeur(getAt(valeurs, i, tailleElement)) - moyenneValeurs;
        differenceCarree += ecart * ecart;
    }

    return sqrt(differenceCarree / (double) taille);
}

