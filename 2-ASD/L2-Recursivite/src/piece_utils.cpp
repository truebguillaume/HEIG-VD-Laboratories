//
// Created by ValentinRicard on 09.03.2023.
//

#include <optional>
#include "piece_utils.h"
#ifdef DOCTEST_ENABLED
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#endif
#include "doctest.h"

AttachementType getOppose(AttachementType attachment) {
    // On part du principe que les nouveaux attachments sont encore positionnés de la facon actuelle:
    // - Des paires d'éléments opposés
    // - Un élément final (NONE) si il n'y a pas d'attachments
    if (attachment == NONE) {
        return NONE;
    } else if (attachment % 2 == 0) {
        // Nous sommes sur le premier élément de la paire
        return (AttachementType) (attachment + 1);
    } else {
        // On est sur une piece impaire
        return (AttachementType) (attachment - 1);
    }
}

TEST_SUITE("piece_utils") {
    TEST_CASE("Testing the opposite function") {
        CHECK(getOppose(ARROSOIR_INVERSE) == NONE);
        CHECK(getOppose(ARROSOIR_DROIT) == ARROSOIR_GAUCHE);
        CHECK(getOppose(ARROSOIR_GAUCHE) == ARROSOIR_DROIT);
        CHECK(getOppose(DAME_HAUT) == DAME_BAS);
        CHECK(getOppose(DAME_BAS) == DAME_HAUT);
    }
}
