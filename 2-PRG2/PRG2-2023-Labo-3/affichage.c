//---------------------------------------------------------
// Labo           : LABO3 - Bateaux
// Classe         : PRG2
// Fichier        : affichage_bateau.c
// Auteur(s)      : Valentin Ricard, Gwendal Piemontesi,
//                  Guillaume Trueb
// But            : Permet l'affichage des détails de bateaux.
// Remarque(s)    : En cas de rajout de catégorie de bateaux,
//                  il faut modifier le tri comptage en fonction.
//---------------------------------------------------------

#include <stdio.h>
#include "affichage.h"

// Retourne en affichage la sous-catégorie du bateau
char* getTypeMoteur(Bateau* bateau) {
    switch (bateau->details.moteur.sous_categorie) {
        case PECHE:
            return "Bateau de peche";
        case LOISIR:
            return "Bateau de loisir";
        default:
            return "Inconnu a moteur";
    }
}

// Retourne en affichage la catégorie du bateau
char* getType(Bateau* bateau) {
    switch (bateau->categorie) {
        case VOILIER:
            return "Voilier";
        case MOTEUR:
            return getTypeMoteur(bateau);
        default:
            return "Inconnu";
    }
}

// Dans le cas ou notre bateau est un voilier
void afficherVoilier(Bateau* bateau) {
    printf("Voilure   : %dm2\n", bateau->details.voilier.voilure);
}

// Affiche les détails lors ce que le bateau à moteur est un bateau de pêche
void afficherBateauMoteurPeche(Bateau* bateau) {
    printf("Tonnes de poissons : %dt\n", bateau->details.moteur.details.peche.max_tonnes_poisson);
}

// Affiche les détails lors ce que le bateau à moteur est un bateau de loisir
void afficherBateauMoteurLoisir(Bateau* bateau) {
    printf("Longueur           : %dm\n", bateau->details.moteur.details.loisir.longueur);
    printf("Proprietaire       : %s\n", bateau->details.moteur.details.loisir.proprietaire);
}

// Dans le cas ou notre bateau à un moteur
void afficherBateauMoteur(Bateau* bateau) {

    printf("Puissance moteur   : %dcv\n", bateau->details.moteur.puissance_moteur);

    // Les bateaux à moteur ont deux sous-catégorie
    switch (bateau->details.moteur.sous_categorie) {
        case PECHE:
            afficherBateauMoteurPeche(bateau);
            break;
        case LOISIR:
            afficherBateauMoteurLoisir(bateau);
            break;
    }
}

void afficherBateau(BateauAvecTaxe* bateau) {
    printf("Nom       : %s\n", bateau->bateau->nom);
    printf("Taxe      : %d.-\n", bateau->taxe);
    printf("Categorie : %s\n", getType(bateau->bateau));

    // En fonction du type de bateau l'affichage est différent
    switch (bateau->bateau->categorie) {
        case VOILIER:
            afficherVoilier(bateau->bateau);
            break;
        case MOTEUR:
            afficherBateauMoteur(bateau->bateau);
            break;
    }
}

void afficherPort(BateauAvecTaxe* port, size_t taillePort) {
    for (size_t t = 0; t < taillePort; ++t) {
        if (t != 0) {
            printf("-----------------------------------------------------------\n");
        }
        afficherBateau(&port[t]);
    }
}

void afficherStat(const char* nom, const Stats* stats) {
    printf("%s :\n"
           "Somme      : %d\n"
           "Moyenne    : %.2f\n"
           "Mediane    : %.2f\n"
           "Ecart-type : %.2f\n",
           nom,
           stats->somme,
           stats->moyenne,
           stats->mediane,
           stats->ecartType);
}

void afficherStats(BateauAvecTaxe* portTrie, size_t taille_port) {
    // Compteurs pour le tri comptage
    int compteurVoilier = 0;
    int compteurPeche = 0;
    int compteurLoisir = 0;

    // On refait le comptage pour connaitre le nombre d'éléments par catégorie et sous-catégorie
    for (size_t i = 0; i < taille_port; ++i) {

        if (portTrie[i].bateau->categorie == VOILIER) {
            ++compteurVoilier;
        } else if (portTrie[i].bateau->categorie == MOTEUR) {
            if (portTrie[i].bateau->details.moteur.sous_categorie == PECHE) {
                ++compteurPeche;
            } else if (portTrie[i].bateau->details.moteur.sous_categorie == LOISIR) {
                ++compteurLoisir;
            }
        }
    }

    Stats statsVoilier = getStats(portTrie + 0, compteurVoilier);
    afficherStat("Bateau voilier", &statsVoilier);

    printf("-----------------------------------------------------------\n");

    Stats statsPeche = getStats(portTrie + 0, compteurPeche);
    afficherStat("Bateau de peche", &statsPeche);

    printf("-----------------------------------------------------------\n");

    Stats statsLoisir = getStats(portTrie + 0, compteurLoisir);
    afficherStat("Bateau de loisir", &statsLoisir);
}
