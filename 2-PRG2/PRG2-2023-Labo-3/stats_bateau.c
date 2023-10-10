//---------------------------------------------------------
// Labo           : LABO3 - Bateaux
// Classe         : PRG2
// Fichier        : stats_bateau.c
// Auteur(s)      : Valentin Ricard, Gwendal Piemontesi,
//                  Guillaume Trueb
// But            : Implémente les statistiques de bateaux.
// Remarque(s)    : Cette implémentation utilise un tri
//                  comptage pour faciliter le travail.
//---------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "stats_bateau.h"

// Trie les bateaux par categories
BateauAvecTaxe* trierParCategories(BateauAvecTaxe* port, size_t taille_port) {

    // Alloue un tableau local
    BateauAvecTaxe* tri = calloc(taille_port, sizeof(BateauAvecTaxe));

    // Contrôle que l'allocation de tri ait bien fonctionné
    if(tri == NULL)
        return NULL;

    // Compteurs pour le tri comptage
    int compteurVoilier = 0;
    int compteurPeche = 0;
    int compteurLoisir = 0;

    // Incrémente les index des valeurs
    for (size_t i = 0; i < taille_port; ++i) {

        if (port[i].bateau->categorie == VOILIER) {
            ++compteurVoilier;
        } else if (port[i].bateau->categorie == MOTEUR) {
            if (port[i].bateau->details.moteur.sous_categorie == PECHE) {
                ++compteurPeche;
            } else if (port[i].bateau->details.moteur.sous_categorie == LOISIR) {
                ++compteurLoisir;
            }
        }
    }

    //Initialiser les index pour l'insertion du tri comptage
    int posVoilier = 0;
    int posPeche = compteurVoilier;
    int posLoisir = posPeche + compteurPeche;

    // Boucle qui remplit le nouveau port trié
    for (size_t i = 0; i < taille_port; ++i) {

        if (port[i].bateau->categorie == VOILIER) {
            tri[posVoilier] = port[i];
            ++posVoilier;
        } else if (port[i].bateau->categorie == MOTEUR) {
            if (port[i].bateau->details.moteur.sous_categorie == PECHE) {
                tri[posPeche] = port[i];
                ++posPeche;
            } else if (port[i].bateau->details.moteur.sous_categorie == LOISIR) {
                tri[posLoisir] = port[i];
                ++posLoisir;
            }
        }
    }
    return tri;
}

// Compare la taxes des bateaux
int compareBateau(BateauAvecTaxe* b1, BateauAvecTaxe* b2) {
    // trie les bateaux en ordre décroissant
    if (b2->taxe > b1->taxe) return 1;
    if (b2->taxe == b1->taxe) return 0;
    return -1;
}

// Trie les bateaux par taxes
void trierParTaxes(BateauAvecTaxe tableau[], size_t taille) {
    qsort(tableau, taille, sizeof(*tableau), (int (*)(const void*, const void*)) compareBateau);
}



// Retourne la taxe du bateau
int getValeur(BateauAvecTaxe* bateauAvecTaxe) {
    return bateauAvecTaxe->taxe;
}

// Recuperer les statistiques
Stats getStats(BateauAvecTaxe* bateaux, size_t taille) {
    Stats stats = {
            .somme = somme(bateaux, taille, sizeof(BateauAvecTaxe), (int (*)(const void*)) getValeur),
            .moyenne = moyenne(bateaux, taille, sizeof(BateauAvecTaxe), (int (*)(const void*)) getValeur),
            .mediane = mediane(bateaux, taille, sizeof(BateauAvecTaxe), (int (*)(const void*)) getValeur),
            .ecartType = ecartType(bateaux, taille, sizeof(BateauAvecTaxe), (int (*)(const void*)) getValeur)
    };

    return stats;
}
