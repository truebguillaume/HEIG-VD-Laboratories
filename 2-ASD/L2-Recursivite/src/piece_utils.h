//
// Created by ValentinRicard on 09.03.2023.
//

#ifndef ASD2022_L2_RECURSIVITE_PIECE_UTILS_H
#define ASD2022_L2_RECURSIVITE_PIECE_UTILS_H

#include <optional>
#include "pieces.h"
#include "placement.h"

AttachementType getOppose(AttachementType attachment);

std::optional<short> aligner(const Piece &piece, AttachementType attachementType, CoteCarte target);


#endif //ASD2022_L2_RECURSIVITE_PIECE_UTILS_H
