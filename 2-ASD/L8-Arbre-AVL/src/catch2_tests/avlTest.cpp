#define CATCH_CONFIG_FAST_COMPILE

#include "catch_amalgamated.hpp"
#include "../avlTree.h"

#include <sstream>
#include <string>

using namespace std;

avlTree<int> make_easy_test_tree() { // order of insertion requires AVL no balancing
    avlTree<int> tree;
    for (int i: {6, 3, 9, 2, 4, 7, 10, 1, 5, 8})
        tree.insert(i);
    return tree;
}

avlTree<int> make_tree(const std::vector<int> &values) {
    avlTree<int> tree;
    for (auto value: values) {
        tree.insert(value);
    }

    return tree;
}

static const std::string EASY_TREE_REPRESENTATION = "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))";

std::string to_string(avlTree<int> &tree) {
    ostringstream out;
    out << tree;
    return out.str();
}

TEST_CASE("insert", "[avlTree]") {

    SECTION("Insert into empty tree") {
        avlTree<int> tree;
        tree.insert(42);

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "42\n");
    }

    SECTION("Insert smaller to the left") {
        avlTree<int> tree;
        tree.insert(3);
        tree.insert(2);

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "3\n"
                             "|_ 2\n"
                             "|_ .\n");
    }

    SECTION("Insert larger to the right") {
        avlTree<int> tree;
        tree.insert(3);
        tree.insert(4);

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "3\n"
                             "|_ .\n"
                             "|_ 4\n");
    }

    SECTION("Insert twice has no effect") {
        avlTree<int> tree;
        tree.insert(3);
        tree.insert(4);
        tree.insert(4);

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "3\n"
                             "|_ .\n"
                             "|_ 4\n");
    }

    SECTION("Easy tree") {
        avlTree<int> tree = make_easy_test_tree();

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "6\n"
                             "|_ 3\n"
                             "|  |_ 2\n"
                             "|  |  |_ 1\n"
                             "|  |  |_ .\n"
                             "|  |_ 4\n"
                             "|     |_ .\n"
                             "|     |_ 5\n"
                             "|_ 9\n"
                             "   |_ 7\n"
                             "   |  |_ .\n"
                             "   |  |_ 8\n"
                             "   |_ 10\n");
    }

    SECTION("Left rotation test") {
        avlTree<int> tree = make_tree({2, 3, 5});
        REQUIRE(to_string(tree) == "3(2(.,.),5(.,.))");
    }

    SECTION("Right rotation test") {
        avlTree<int> tree = make_tree({5, 2, 1});
        REQUIRE(to_string(tree) == "2(1(.,.),5(.,.))");
    }

    SECTION("Left Right rotation test") {
        avlTree<int> tree = make_tree({4, 3, 8, 9, 6, 9, 5});
        REQUIRE(to_string(tree) == "6(4(3(.,.),5(.,.)),8(.,9(.,.)))");
    }

    SECTION("Test from previous exam") {
        avlTree<int> tree = make_tree({3, 1, 6, 2, 5, 8, 4, 7, 9, 10});
        REQUIRE(to_string(tree) == "6(3(1(.,2(.,.)),5(4(.,.),.)),8(7(.,.),9(.,10(.,.))))");
    }
}

TEST_CASE("display_indented", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> tree;

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == ".\n");
    }

    SECTION("Easy test tree") {
        avlTree<int> tree = make_easy_test_tree();

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "6\n"
                             "|_ 3\n"
                             "|  |_ 2\n"
                             "|  |  |_ 1\n"
                             "|  |  |_ .\n"
                             "|  |_ 4\n"
                             "|     |_ .\n"
                             "|     |_ 5\n"
                             "|_ 9\n"
                             "   |_ 7\n"
                             "   |  |_ .\n"
                             "   |  |_ 8\n"
                             "   |_ 10\n");
    }
}

TEST_CASE("operator<<", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> tree;

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == ".");
    }

    SECTION("Easy test tree") {
        avlTree<int> tree = make_easy_test_tree();

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
    }
}

TEST_CASE("operator>>", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> tree;

        istringstream iss;
        iss.str(".");
        iss >> tree;

        REQUIRE(to_string(tree) == ".");
    }

    SECTION("Easy test tree") {
        avlTree<int> tree = make_easy_test_tree();

        istringstream iss;
        iss.str("6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
        iss >> tree;

        REQUIRE(to_string(tree) == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
    }
}

TEST_CASE("Copy Constructor", "[avlTree]") {
    SECTION("Copy empty tree") {
        avlTree<int> initial;
        REQUIRE(to_string(initial) == ".");
        avlTree<int> cloned(initial);
        // Vérifie que l'initial n'est pas touché, et que la copie fonctionne
        REQUIRE(to_string(initial) == ".");
        REQUIRE(to_string(cloned) == ".");
        // Insérer dans initial
        initial.insert(11);
        // Vérifier que ca n'est pas propagé dans la copie
        REQUIRE(to_string(cloned) == ".");
    }

    SECTION("Copy easy tree") {
        avlTree<int> initial = make_easy_test_tree();
        avlTree<int> cloned(initial);
        // Vérifie que l'initial n'est pas touché, et que la copie fonctionne
        REQUIRE(to_string(initial) == EASY_TREE_REPRESENTATION);
        REQUIRE(to_string(cloned) == EASY_TREE_REPRESENTATION);
        // Insérer dans initial
        initial.insert(11);
        // Vérifier que ca n'est pas propagé dans la copie
        REQUIRE(to_string(cloned) == EASY_TREE_REPRESENTATION);
    }
}

TEST_CASE("Erase Key", "[avlTree]") {
    SECTION("Single element") {
        avlTree<int> tree;
        tree.insert(2);
        REQUIRE(to_string(tree) == "2(.,.)");
        tree.erase(2);
        REQUIRE(to_string(tree) == ".");
    }

    SECTION("Easy erase") {
        avlTree<int> tree = make_easy_test_tree();
        tree.erase(10);
        REQUIRE(to_string(tree) == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),.))");
    }

    SECTION("Erase with children") {
        avlTree<int> tree = make_easy_test_tree();
        tree.erase(9);
        REQUIRE(to_string(tree) == "6(3(2(1(.,.),.),4(.,5(.,.))),10(7(.,8(.,.)),.))");
    }
}

TEST_CASE("Erase Min", "[avlTree]") {
    SECTION("Erase min with childs") {
        avlTree<int> tree = make_tree({8, 5, 9, 3, 4});
        tree.erase_min();
        REQUIRE(to_string(tree) == "5(4(.,.),8(.,9(.,.)))");
    }
    SECTION("Erase min with no children") {
        avlTree<int> tree = make_tree({5, 4, 6, 3});
        tree.erase_min();
        REQUIRE(to_string(tree) == "5(4(.,.),6(.,.))");
    }
    SECTION("Erase min as root") {
        avlTree<int> tree;
        tree.insert(1);
        tree.erase_min();
        REQUIRE(to_string(tree) == ".");
    }
}

TEST_CASE("Erase Max", "[avlTree]") {
    SECTION("Erase max with childs") {
        avlTree<int> tree = make_tree({8, 5, 9, 3, 4, 7});
        tree.erase_max();
        REQUIRE(to_string(tree) == "5(3(.,4(.,.)),8(7(.,.),.))");
    }

    SECTION("Erase max with no children") {
        avlTree<int> tree = make_easy_test_tree();
        tree.erase_max();
        REQUIRE(to_string(tree) == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),.))");
    }

    SECTION("Erase max as root") {
        avlTree<int> tree;
        tree.insert(1);
        tree.erase_max();
        REQUIRE(to_string(tree) == ".");
    }
}

TEST_CASE("Assignment", "[avlTree]") {
    SECTION("Same assignation") {
        avlTree<int> initial = make_easy_test_tree();
        initial = initial;
        REQUIRE(to_string(initial) == EASY_TREE_REPRESENTATION);
    }

    SECTION("Copy empty tree") {
        avlTree<int> initial;
        REQUIRE(to_string(initial) == ".");
        avlTree<int> cloned;
        cloned = initial;
        // Vérifie que l'initial n'est pas touché, et que la copie fonctionne
        REQUIRE(to_string(initial) == ".");
        REQUIRE(to_string(cloned) == ".");
        // Insérer dans initial
        initial.insert(11);
        // Vérifier que ca n'est pas propagé dans la copie
        REQUIRE(to_string(cloned) == ".");
    }

    SECTION("Copy easy tree") {
        avlTree<int> initial = make_easy_test_tree();
        avlTree<int> cloned;
        cloned = initial;
        // Vérifie que l'initial n'est pas touché, et que la copie fonctionne
        REQUIRE(to_string(initial) == EASY_TREE_REPRESENTATION);
        REQUIRE(to_string(cloned) == EASY_TREE_REPRESENTATION);
        // Insérer dans initial
        initial.insert(11);
        // Vérifier que ca n'est pas propagé dans la copie
        REQUIRE(to_string(cloned) == EASY_TREE_REPRESENTATION);
    }
}

TEST_CASE("min()", "[avlTree]") {
    SECTION("Single node tree") {
        avlTree<int> tree;
        tree.insert(2);
        REQUIRE(tree.min() == 2);
    }

    SECTION("Easy tree") {
        avlTree<int> tree = make_easy_test_tree();
        REQUIRE(tree.min() == 1);
    }
}

TEST_CASE("max()", "[avlTree]") {
    SECTION("Single node tree") {
        avlTree<int> tree;
        tree.insert(2);
        REQUIRE(tree.max() == 2);
    }

    SECTION("Easy tree") {
        avlTree<int> tree = make_easy_test_tree();
        REQUIRE(tree.max() == 10);
    }
}

TEST_CASE("height", "[avlTree]") {
    SECTION("Empty tree") {
        avlTree<int> tree;
        REQUIRE(tree.height() == 0);
    }
    SECTION("Easy tree") {
        avlTree<int> tree = make_easy_test_tree();
        REQUIRE(tree.height() == 4);
    }
}

TEST_CASE("contains", "[avlTree]") {
    SECTION("Single node") {
        avlTree<int> tree;
        tree.insert(2);
        REQUIRE(tree.contains(2) == true);
        REQUIRE(tree.contains(3) == false);
    }

    SECTION("Easy tree") {
        avlTree<int> tree = make_easy_test_tree();
        REQUIRE(tree.contains(3) == true);
        REQUIRE(tree.contains(11) == false);
    }
}