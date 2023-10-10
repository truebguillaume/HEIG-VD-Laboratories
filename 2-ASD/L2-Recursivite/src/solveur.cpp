//
// Created by Guillaume Trüeb on 09.03.23.
//
#include "solveur.h"
#include <algorithm>
#include <iostream>

using namespace std;

Solveur::Solveur(const Pieces &pieces, const function<void(const std::vector<Placement> &)> &lorsResultat)
        : pieces(pieces), lorsResultat(lorsResultat) {}

void Solveur::solve() {

    vector<Placement> placements(PIECES.size());


    for (size_t piece = 0; piece < PIECES.size(); ++piece) {
        placements[piece] = {piece, 0};
    }

    // On récupère une pièce, et on fait toutes les rotations
    for (size_t piece = 0; piece < placements.size(); ++piece) {
        swap(placements[0], placements[piece]);
        for (Rotation rotation = 0; rotation < 4; ++rotation) {
            placements[0] = {piece, rotation};
            _solve(placements, 1);
        }
        swap(placements[0], placements[piece]);
    }
}

size_t Solveur::getNombreOperations() const {
    return nombreOperations;
}

void Solveur::_solve(std::vector<Placement> &placements, size_t n) {
    ++nombreOperations;

    AttachementType attachementATrouver;

    // Si on a placé toutes les pièces
    if (n == placements.size()) {
        // On appelle la fonction lorsResultat qui affiche la solution
        lorsResultat(placements);
        return;
    }

    // Partie 1 : fixer l'attachement à trouver
    if (n % 3 != 0) {
        attachementATrouver = getOppose(placements[n - 1].getCote(CoteCarte::DROITE));
    } else {
        attachementATrouver = getOppose(placements[n - 3].getCote(CoteCarte::BAS));
    }

    for (size_t i = n; i < placements.size(); ++i) {

        bool attachementTrouve = false;

        if (n % 3 != 0) {
            attachementTrouve = placements[i].aligner(attachementATrouver, CoteCarte::GAUCHE);
        } else {
            attachementTrouve = placements[i].aligner(attachementATrouver, CoteCarte::HAUT);
        }

        if (attachementTrouve) {
            // Partie 2 : check si on peut placer la pièce en haut
            if (n % 3 != 0 && n > 3) {
                auto expected = getOppose(placements[n - 3].getCote(CoteCarte::BAS));
                auto actual = placements[i].getCote(CoteCarte::HAUT);
                if (expected != actual) {
                    continue;
                }
            }

            swap(placements[n], placements[i]);
            _solve(placements, n + 1);
            swap(placements[n], placements[i]);
        }
    }
}
