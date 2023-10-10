//---------------------------------------------------------
// Labo           : LABO3 - Bateaux
// Classe         : PRG2
// Fichier        : affichage_bateau.h
// Auteur(s)      : Valentin Ricard, Gwendal Piemontesi,
//                  Guillaume Trueb
// But            : Permet l'affichage des détails de bateaux.
// Remarque(s)    : Ce module utilise un bateau avec taxes afin d'éviter
//                  de re-calculer les taxes plusieurs fois.
//---------------------------------------------------------

#ifndef PRG2_LABO3_AFFICHAGE_H
#define PRG2_LABO3_AFFICHAGE_H

#include <stdlib.h>
#include "bateau.h"
#include "stats_bateau.h"

// Affiche les détails d'un bateau avec taxes
void afficherBateau(BateauAvecTaxe* bateau);

// Affiche un port qui est un tableau de bateaux avec taxes
void afficherPort(BateauAvecTaxe* port, size_t taillePort);

// Affiche les stats du port
void afficherStats(BateauAvecTaxe* portTrie, size_t taille_port);

#endif //PRG2_LABO3_AFFICHAGE_H
