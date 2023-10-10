//---------------------------------------------------------
// Labo           : LABO3 - Bateaux
// Classe         : PRG2
// Fichier        : main.c
// Auteur(s)      : Valentin Ricard, Gwendal Piemontesi,
//                  Guillaume Trueb
// But            : Permet de recuperer les taxes de différents bateaux,
//                  et d'afficher des statistiques sur le port.
// Remarque(s)    : Afin de changer la composition du port, il faut modifier la liste port.
//---------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include "bateau.h"
#include "stats_bateau.h"
#include "affichage.h"


int main() {

    // Changer la composition du port ici.
    Bateau port[] = {
            creerVoilier("La bicoque", 250),
            creerVoilier("Le radeau", 50),
            creerBateauPeche("Le chalut", 150, 6),
            creerBateauPeche("La bequille", 200, 25),
            creerBateauLoisir("Le tir-bouchon", 300, 7, "Guy Parmelin"),
            creerBateauLoisir("Le fondant", 150, 15, "Christian Constentin"),
    };

    const size_t taillePort = sizeof(port) / sizeof(port[0]);

    // On déclare un nouveau tableau, avec les taxes, pour éviter de recalculer à nouveau les éléments
    BateauAvecTaxe* portBateauxAvecTaxe = calloc(taillePort, sizeof(BateauAvecTaxe));

    // Contrôle que l'allocation du portBateauxAvecTaxe ait bien fonctionné
    if(portBateauxAvecTaxe == NULL)
        return EXIT_FAILURE;

    for (size_t i = 0; i < taillePort; ++i) {
        Bateau* bateau = port + i;

        portBateauxAvecTaxe[i].bateau = bateau;
        portBateauxAvecTaxe[i].taxe = taxes(bateau);
    }

    printf("==========================PORT=============================\n");
    trierParTaxes(portBateauxAvecTaxe, taillePort);
    afficherPort(portBateauxAvecTaxe, taillePort);

    printf("\n==========================STATS============================\n");
    BateauAvecTaxe* portParCategorie = trierParCategories(portBateauxAvecTaxe, taillePort);

    // Contrôle que l'allocation du portParCategorie ait bien fonctionné
    if(portParCategorie == NULL)
        return EXIT_FAILURE;

    afficherStats(portParCategorie, taillePort);
    free(portParCategorie);
    printf("===========================================================\n");

    free(portBateauxAvecTaxe);

    return 0;
}
