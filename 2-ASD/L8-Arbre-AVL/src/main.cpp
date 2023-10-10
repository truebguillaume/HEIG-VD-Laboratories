#include <iostream>
#include <sstream>
#include "avlTree.h"

using namespace std;

int main() {

	avlTree<int> t;

    for (int i : { 8,4,11,1,10,12 })
    {
        t.insert(i);
        cout << endl;
    }

    t.show_indented(cout);

    t.erase(8);

    t.show_indented(cout);

	return EXIT_SUCCESS;
}