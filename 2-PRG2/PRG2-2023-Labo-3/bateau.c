//---------------------------------------------------------
// Labo           : LABO3 - Bateaux
// Classe         : PRG2
// Fichier        : bateau.c
// Auteur(s)      : Valentin Ricard, Gwendal Piemontesi,
//                  Guillaume Trueb
// But            : Implémente les algorithmes liés à la structure bateau.
// Remarque(s)    : En cas de rajout de catégorie de bateaux,
//                  il faut modifier l'implémentation de la fonction taxe.
//---------------------------------------------------------

#include "bateau.h"

// Constantes de prix permettant de calculer les taxes pour nos différents bateaux
const int TAXE_VOILIER = 50;
const int TAXE_MOTEUR = 100;
const int TAXE_SUP_GRAND_VOILER = 25;
const int TAXE_SUP_PETIT_PECHE = 0;
const int TAXE_SUP_GRAND_PECHE = 100;
const int TAXE_SUP_PETIT_LOISIR = 50;
const int TAXE_SUP_RATIO_LOISIR = 15;
const int LIMITE_MOTEUR_LOISIR = 100;
const int LIMITE_TONNAGE_PECHE = 20;
const int LIMITE_SURFACE_VOILURE = 200;

Bateau creerVoilier(const char* nom, uint16_t surfaceVoilure) {
    Bateau result = {
            .nom = nom,
            .categorie = VOILIER,
            .details.voilier = {
                    .voilure = surfaceVoilure
            }
    };

    return result;
}

Bateau creerBateauLoisir(const char* nom, uint16_t puissanceMoteur, uint8_t longueur, const char* proprietaire) {
    Bateau result = {
            .nom = nom,
            .categorie = MOTEUR,
            .details.moteur = {
                    .puissance_moteur = puissanceMoteur,
                    .sous_categorie = LOISIR,
                    .details.loisir = {
                            .longueur = longueur,
                            .proprietaire = proprietaire
                    }
            }
    };

    return result;
}

Bateau creerBateauPeche(const char* nom, uint16_t puissanceMoteur, uint8_t maxTonnesPoisson) {
    Bateau result = {
            .nom = nom,
            .categorie = MOTEUR,
            .details.moteur = {
                    .puissance_moteur = puissanceMoteur,
                    .sous_categorie = PECHE,
                    .details.peche = {
                            .max_tonnes_poisson = maxTonnesPoisson
                    }
            }
    };
    return result;
}

// Retourne la taxe en fonction de la taille de la voilure pour les voiliers
int taxeVoilier(const Voilier* voilier) {
    int tax = TAXE_VOILIER;

    if (voilier->voilure > LIMITE_SURFACE_VOILURE) {
        tax += TAXE_SUP_GRAND_VOILER;
    }

    return tax;
}

// Retourne la taxe en fonction de la puissance du moteur pour les bateaux
// de loisir
int taxeLoisir(const Moteur* moteur) {
    if (moteur->puissance_moteur < LIMITE_MOTEUR_LOISIR) {
        return TAXE_SUP_PETIT_LOISIR;
    }

    return moteur->details.loisir.longueur * TAXE_SUP_RATIO_LOISIR;
}

// Retourne la taxe en fonction du nb de tonnes de poisson que le bateau
// peut transporter
int taxePeche(const Moteur* moteur) {
    if (moteur->details.peche.max_tonnes_poisson < LIMITE_TONNAGE_PECHE) {
        return TAXE_SUP_PETIT_PECHE;
    }
    return TAXE_SUP_GRAND_PECHE;
}

// Retourne la taxe liée au moteur en question et appelle la fonction
// retournant la taxe liée aux sous-catégories
int taxeMoteur(const Moteur* moteur) {
    switch (moteur->sous_categorie) {
        case PECHE:
            return TAXE_MOTEUR + taxePeche(moteur);
        case LOISIR:
            return TAXE_MOTEUR + taxeLoisir(moteur);
        default:
            return -1;
    }
}

int taxes(const Bateau* bateau) {
    switch (bateau->categorie) {
        case VOILIER:
            return taxeVoilier(&bateau->details.voilier);
        case MOTEUR:
            return taxeMoteur(&bateau->details.moteur);
        default:
            return -1;
    }
}

