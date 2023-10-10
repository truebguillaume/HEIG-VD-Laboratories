#include <iostream>
#include "pieces.h"
#include "solveur.h"

using namespace std;

int main() {

    Pieces pieces = PIECES;

    Solveur solveur(pieces, [](auto placements) {
        for (const Placement& placement : placements) {
            cout << placement.getIndex()+1 << (char)('a' + placement.getRotation()) << " ";
        }
        cout << endl;
    });

    solveur.solve();

    cout << "Nombre d'appels de la recursion: " << solveur.getNombreOperations();
}

