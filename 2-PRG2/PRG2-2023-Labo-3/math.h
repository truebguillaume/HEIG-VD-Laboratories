//---------------------------------------------------------
// Labo           : LABO3 - Bateaux
// Classe         : PRG2
// Fichier        : math.h
// Auteur(s)      : Valentin Ricard, Gwendal Piemontesi,
//                  Guillaume Trueb
// But            : Définit une série d'utilitaires pour le calcul de statistiques "génériques"
// Remarque(s)    : Les fonctions de cette classe sont "génériques", s'inspirant de la fonction
//                  qsort de la librairie standard.
//                  La complexité supplémentaire est justifiable par sa flexibilité et
//                  modularité supplémentaire.
//---------------------------------------------------------

#ifndef PRG2_LABO3_MATH_H
#define PRG2_LABO3_MATH_H

#include <stddef.h>

unsigned int somme(const void* element, size_t taille, size_t tailleElement, int (* versValeur)(const void* pointeur));

double moyenne(const void* element, size_t taille, size_t tailleElement, int (* versValeur)(const void* pointeur));

double mediane(const void* valeurs, size_t taille, size_t tailleElement, int (* versValeur)(const void* pointeur));

double ecartType(const void* valeurs, size_t taille, size_t tailleElement, int (* versValeur)(const void* pointeur));

#endif //PRG2_LABO3_MATH_H
