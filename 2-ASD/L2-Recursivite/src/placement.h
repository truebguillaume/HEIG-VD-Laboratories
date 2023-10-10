//
// Created by Gwendal on 09.03.2023.
//

#ifndef ASD2023_L2_RECURSIVITE_PLACEMENT_H
#define ASD2023_L2_RECURSIVITE_PLACEMENT_H

#include "pieces.h"
#include <ostream>
#include <string>

using Rotation = short;

enum class CoteCarte: Rotation {
    HAUT = 0,
    DROITE,
    BAS,
    GAUCHE
};
constexpr std::array COTE_CARTES = {CoteCarte::HAUT, CoteCarte::DROITE, CoteCarte::BAS, CoteCarte::GAUCHE};

class Placement {
public:
    friend std::ostream &operator<<(std::ostream& os, const Placement& placement);

    Placement() : index(0), rotation(0) {}
    Placement(size_t index) : index(index), rotation(0) {}
    Placement(size_t index, Rotation rotation): index(index), rotation(rotation) {}

    AttachementType getCote(CoteCarte pos);
    size_t getIndex() const { return index; }
    Rotation getRotation() const;
    void  setRotation(Rotation r);
    const Piece& getPiece();
    bool aligner(AttachementType attachment, CoteCarte coteCarte);
private:
    size_t index;
    short rotation;
};

#endif //ASD2023_L2_RECURSIVITE_PLACEMENT_H
