//---------------------------------------------------------
// Labo           : LABO3 - Bateaux
// Classe         : PRG2
// Fichier        : stats_bateau.h
// Auteur(s)      : Valentin Ricard, Gwendal Piemontesi,
//                  Guillaume Trueb
// But            : Définit une structure pour les statistiques de bateaux.
// Remarque(s)    : Afin d'éviter de copier les Bateaux, un pointeur est utilisé pour économiser
//                  de la mémoire et accélérer les tris
//---------------------------------------------------------

#ifndef PRG2_LABO3_STATS_BATEAU_H
#define PRG2_LABO3_STATS_BATEAU_H

#include "bateau.h"

// Structure de bateau avec sa taxe
typedef struct {
    Bateau* bateau;
    int taxe;
} BateauAvecTaxe;

// Structure de statistique
typedef struct {
    unsigned int somme;
    double moyenne;
    double mediane;
    double ecartType;
} Stats;

// Trie les bateaux par taxes
void trierParTaxes(BateauAvecTaxe* tableau, size_t taille);

// Trie les bateaux par categories
BateauAvecTaxe* trierParCategories(BateauAvecTaxe* port, size_t taille_port);

// Recuperer les statistiques
Stats getStats(BateauAvecTaxe* bateaux, size_t taille);

#endif //PRG2_LABO3_STATS_BATEAU_H
