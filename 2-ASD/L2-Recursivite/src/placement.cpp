//
// Created by Gwendal on 09.03.2023.
//

#include "placement.h"
#include "piece_utils.h"
#include "doctest.h"

std::ostream &operator<<(std::ostream &os, const Placement &placement) {
    os << (placement.index + 1) << (char) ('a' + placement.rotation);

    return os;
}

AttachementType Placement::getCote(CoteCarte pos) {
    return getPiece()[(std::size_t) (rotation + (Rotation) pos) % 4];
}

Rotation Placement::getRotation() const {
    return rotation;
}

void Placement::setRotation(Rotation r) {
    rotation = r;
}

const Piece &Placement::getPiece() {
    return PIECES[index];
}

bool Placement::aligner(AttachementType attachement, CoteCarte coteVoulu) {
    auto piece = getPiece();

    for (auto iter : COTE_CARTES) {
        if (piece[(std::size_t) iter] == attachement) {
            // On a le symbole voulu, on peut donc trouver et définir la rotation.
            auto rotation = (Rotation) ((4 + (int) iter - (int) coteVoulu) % 4);
            setRotation(rotation);
            return true;
        }
    }

    return false;
}


//Tests
TEST_SUITE("Test placement") {
    Placement getPlacement(size_t index, AttachementType type, CoteCarte rotation) {
        Placement placement = Placement(index, 0);
        placement.aligner(type, rotation);
        return placement;
    }

    TEST_CASE("Testing the placement function") {
        Placement placement = Placement(0, 0);

        placement.aligner(DAME_HAUT, CoteCarte::HAUT);
        CHECK_EQ(placement.getRotation(), 0);

        placement.aligner(GATEAU_DROIT, CoteCarte::GAUCHE);
        CHECK_EQ(placement.getRotation(), 2);

        placement.aligner(GATEAU_DROIT, CoteCarte::BAS);
        CHECK_EQ(placement.getRotation(), 3);
    }

    TEST_CASE("Testing the placement + getCote function") {
        CHECK_EQ(getPlacement(0, DAME_HAUT, CoteCarte::HAUT).getCote(CoteCarte::HAUT), DAME_HAUT);
        CHECK_EQ(getPlacement(0, GATEAU_DROIT, CoteCarte::GAUCHE).getCote(CoteCarte::GAUCHE), GATEAU_DROIT);
        CHECK_EQ(getPlacement(0, GATEAU_DROIT, CoteCarte::BAS).getCote(CoteCarte::BAS), GATEAU_DROIT);
        CHECK_EQ(getPlacement(0, GATEAU_DROIT, CoteCarte::HAUT).getCote(CoteCarte::HAUT), GATEAU_DROIT);
    }

    TEST_CASE("Test getCote") {
        //Piece 1
        //rotation 0
        Placement placement = {0, 0};
        CHECK_EQ(placement.getCote(CoteCarte::HAUT), DAME_HAUT);
        Placement placement1 = {0, 0};
        CHECK_EQ(placement1.getCote(CoteCarte::DROITE), GATEAU_DROIT);
        Placement placement2 = {0, 0};
        CHECK_EQ(placement2.getCote(CoteCarte::BAS), ARROSOIR_GAUCHE);
        Placement placement3 = {0, 0};
        CHECK_EQ(placement3.getCote(CoteCarte::GAUCHE), FILLE_HAUT);

        //rotation 1
        Placement placement4 = {0, 1};
        CHECK_EQ(placement4.getCote(CoteCarte::HAUT), GATEAU_DROIT);
        Placement placement5 = {0, 1};
        CHECK_EQ(placement5.getCote(CoteCarte::DROITE), ARROSOIR_GAUCHE);
        Placement placement6 = {0, 1};
        CHECK_EQ(placement6.getCote(CoteCarte::BAS), FILLE_HAUT);
        Placement placement7 = {0, 1};
        CHECK_EQ(placement7.getCote(CoteCarte::GAUCHE), DAME_HAUT);
    }
}

