//
// Created by ValentinRicard on 05.06.2023.
//

#ifndef ASD2022_L8_AVL_TREE_PARSER_H
#define ASD2022_L8_AVL_TREE_PARSER_H

#include <istream>

namespace parser {
    class parse_error: std::exception {

    };

    void expect(std::istream &stream, char expectedChar);

    void expectEmpty(std::istream &stream);
}


#endif //ASD2022_L8_AVL_TREE_PARSER_H
