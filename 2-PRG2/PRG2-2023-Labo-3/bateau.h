//---------------------------------------------------------
// Labo           : LABO3 - Bateaux
// Classe         : PRG2
// Fichier        : bateau.h
// Auteur(s)      : Valentin Ricard, Gwendal Piemontesi,
//                  Guillaume Trueb
// But            : Définit la structure de données du bateau,
//                  ainsi que les prototypes de fonctions
// Remarque(s)    : La structure n'utilise pas d'allocation de mémoire par simplicité.
//                  Dans le futur, si une structure venait à être trop grande,
//                  il est possible de mettre un pointeur, et d'allouer l'élément sur le heap.
//---------------------------------------------------------

#ifndef PRG2_LABO3_BATEAU_H
#define PRG2_LABO3_BATEAU_H

#include <stdint.h>

// Structure de sous categories
typedef enum {
    PECHE,
    LOISIR
} SousCategorie;

// Structure de bateau de pêche
typedef struct {
    uint8_t max_tonnes_poisson;
} BateauPeche;

// Structure de bateau de loisir
typedef struct {
    uint8_t longueur;
    const char* proprietaire;
} BateauLoisir;

// Union des details de la sous categorie
typedef union {
    BateauPeche peche;
    BateauLoisir loisir;
} DetailsSousCategorie;

// Enumeration des categories
typedef enum {
    VOILIER,
    MOTEUR
} Categorie;

// Structure de voilier
typedef struct {
    uint16_t voilure;
} Voilier;

// Structure de moteur
typedef struct {
    uint16_t puissance_moteur;
    SousCategorie sous_categorie;
    DetailsSousCategorie details;
} Moteur;

// Union des details de la categorie
typedef union {
    Voilier voilier;
    Moteur moteur;
} CategorieDetails;

// Structure de bateau
typedef struct {
    const char* nom;
    Categorie categorie;
    CategorieDetails details;
} Bateau;

// Retourne la valeur des taxes pour un bateau
int taxes(const Bateau* bateau);

// Permet de créer un voilier en passant les détails par paramètres
Bateau creerVoilier(const char* nom, uint16_t surfaceVoilure);

// Permet de créer un bateau de loisir en passant les détails par paramètres
Bateau creerBateauLoisir(const char* nom, uint16_t puissanceMoteur, uint8_t longueur, const char* proprietaire);

// Permet de créer un bateau de pêche en passant les détails par paramètres
Bateau creerBateauPeche(const char* nom, uint16_t puissanceMoteur, uint8_t maxTonnesPoisson);

#endif //PRG2_LABO3_BATEAU_H
