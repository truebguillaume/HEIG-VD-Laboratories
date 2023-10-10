//
// Created by ValentinRicard on 05.06.2023.
//

#include "parser.h"

void parser::expect(std::istream &stream, char expectedChar) {
    if (stream.get() != expectedChar) {
        throw parse_error();
    }
}

void parser::expectEmpty(std::istream &stream) {
    if (!stream.eof()) {
        throw parse_error();
    }
}
