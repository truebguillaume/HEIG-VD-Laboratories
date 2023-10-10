#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <random>
#include "some_bits.h"
#include "tri_rapide.h"
#include <vector>
#include "tri_par_base.h"

using namespace std;
using ui = unsigned int;

int main() {

    // -----------------------------------------------------------------------------------------------------------------
    // TRI COMPTAGE
    // -----------------------------------------------------------------------------------------------------------------
    cout << "TRI COMPTAGE" << endl;
    vector<ui> v;

    // Remplis un vecteur v avec des nombres allant de 1 à 499 et ajoute 2 fois le nombre si multiple de 3 ou 5.
    // Cela permets de tester les indices pour le tri comptage.
    for(ui i = 0 ; i < 100 ; ++i){
        if(i % 3 == 0 || i % 5 == 0){
            v.insert(v.end(), 2, i);
        }
        else{
            v.push_back(i);
        }
    }

    // Mélange le vecteur
    std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});

    // Création du vecteur de sortie
    vector<ui> vSortie(v.size());

    // Affichage du vecteur non-trié
    for(ui i : v)
        cout << i << " ";
    cout << endl;

    // Appel du tri comptage pour le tester
    tri_comptage<>(v.begin(), v.end(), vSortie.begin(), [](int a){return a;}, v.size());

    // Affichage du vecteur trié
    for(ui i : vSortie)
        cout << i << " ";
    cout << endl << "Est-ce que le vecteur est trié : "
         << boolalpha << is_sorted(vSortie.begin(), vSortie.end()) << endl << endl;

    // -----------------------------------------------------------------------------------------------------------------
    // TRI PAR BASE
    // -----------------------------------------------------------------------------------------------------------------
    cout << "TRI PAR BASE" << endl;
    vector<ui> v2;

    for(ui i = 0 ; i < 100 ; ++i){
        if(i % 3 == 0 || i % 5 == 0){
            v2.insert(v2.end(), 2, i);
        }
        else{
            v2.push_back(i);
        }
    }

    // Mélange le vecteur
    std::shuffle(v2.begin(), v2.end(), std::mt19937{std::random_device{}()});

    // Affichage du vecteur non-trié
    for(ui i : v2)
        cout << i << " ";
    cout << endl;

    // Appel du tri par base
    tri_par_base<vector<ui>::iterator,4>(v2.begin(), v2.end());

    // Affichage du vecteur trié
    for(ui i : v2)
        cout << i << " ";
    cout << endl << "Est-ce que le vecteur est trié : "
         << boolalpha << is_sorted(v2.begin(), v2.end()) << endl << endl;

    // -----------------------------------------------------------------------------------------------------------------
    // TRI RAPIDE
    // -----------------------------------------------------------------------------------------------------------------
    cout << "TRI RAPIDE" << endl;
    vector<int> v3 = {19, 26, 10, 21, 7, 28, 16, 25, 20, 14, 27, 22, 9, 3,
                      2, 23, 12, 13, 6, 18, 5, 4, 29, 8, 15, 30, 1, 24, 11, 17};

    for(int i : v3)
        cout << i << " ";
    cout << endl;

    tri_rapide(v3.begin(), v3.end());

    for(int i : v3)
        cout << i << " ";
    cout << endl;

    cout << "Est-ce que le vecteur est trié : "
         << boolalpha << is_sorted(v3.begin(), v3.end()) << endl << endl;


}