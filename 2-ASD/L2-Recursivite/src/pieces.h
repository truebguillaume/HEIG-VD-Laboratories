//
//  pieces.h
//  Puzzle récursif
//
//  Created by Olivier Cuisenaire on 06.11.18.
//  Copyright © 2018 Olivier Cuisenaire. All rights reserved.
//

#ifndef pieces_h
#define pieces_h

#include <array>
#include <vector>

enum AttachementType {
  FILLE_HAUT,      //0
  FILLE_BAS,       //1
  DAME_HAUT,       //2
  DAME_BAS,        //3
  ARROSOIR_GAUCHE, //4
  ARROSOIR_DROIT,  //5
  GATEAU_GAUCHE,   //6
  GATEAU_DROIT,    //7
  ARROSOIR_INVERSE,//8
  NONE };          //9

using Piece = std::array<AttachementType,4>;
using Pieces = std::vector<Piece>;

extern const Pieces PIECES;

#endif /* pieces_h */
