//
// Created by Guillaume Trüeb on 09.03.23.
//

#ifndef ASD2023_L2_RECURSIVITE_SOLVEUR_H
#define ASD2023_L2_RECURSIVITE_SOLVEUR_H

#include <vector>
#include <functional>
#include "pieces.h"
#include "placement.h"
#include "piece_utils.h"

class Solveur {

public:

    Solveur(const Pieces &pieces, const std::function<void(const std::vector<Placement>&)> &lorsResultat);
    void solve();

    size_t getNombreOperations() const;

private:
    size_t nombreOperations = 0;
    const Pieces& pieces;

    // fonction recursive qui cherche une solution
    void _solve(std::vector<Placement>&, size_t n);

    // pour ecriture de la solution dans une fonction lambda
    const std::function<void(const std::vector<Placement>&)>& lorsResultat;
};


#endif //ASD2023_L2_RECURSIVITE_SOLVEUR_H
