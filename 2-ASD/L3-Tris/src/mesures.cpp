//
// Created by ValentinRicard on 23.03.2023.
//

#include "harnais/TestPerformance.h"
#include <iostream>
#include "harnais/generateurs.h"
#include "tri_par_base.h"
#include "tri_rapide.h"
#include "harnais/FichierCSV.h"

static const int SEED = 12345;
static const size_t NOMBRE_MESURES = 50;

#define TRI_BASE(base, vector) tri_par_base<std::vector<unsigned int>::iterator, static_cast<size_t>(base)>(vector.begin(), vector.end())

int main() {

    // Crée une liste des fonctions à tester.
    std::vector<std::function<void(std::vector<unsigned int>)>> tris = {
            [](auto vector){
                std::sort(vector.begin(), vector.end());
            },
            [](auto vector){
                std::stable_sort(vector.begin(), vector.end());
            },
            [](auto vector){
                tri_rapide(vector.begin(), vector.end());
            },
            [](auto vector) {
                TRI_BASE(1, vector);
            },
            [](auto vector) {
                TRI_BASE(2, vector);
            },
            [](auto vector) {
                TRI_BASE(4, vector);
            },
            [](auto vector) {
                TRI_BASE(8, vector);
            },
            [](auto vector) {
                TRI_BASE(16, vector);
            }
    };

    // Leurs noms correspondants.
    // Il aurait été préférable de le faire avec une seule structure,
    // mais cela aurait complexifié encore plus le code de cette fonction.
    std::array<std::string, 8> nomsTris = {
            "std_sort",
            "std_stable_sort",
            "tri_rapide",
            "tri_base_1",
            "tri_base_2",
            "tri_base_4",
            "tri_base_8",
            "tri_base_16"
    };

    // Crée le fichier CSV de résultats
    FichierCSV csv("resultats.csv", "tri,compte", NOMBRE_MESURES);

    // Pour chaque méthode...
    for (size_t indexMethode = 0; indexMethode < tris.size(); ++indexMethode) {
        // ... et pour chaque taille de vecteur parmi cette liste ...
        for (auto tailleVecteur : {10, 1'000, 10'000, 100'000, 1'000'000}) {
            // Tester la performance, et la rajouter dans le CSV.
            TestPerformance<std::vector<unsigned int>> test = {[&tailleVecteur]() {
                return genererVecteur<unsigned int>((size_t) tailleVecteur, GeneratorType::RANDOM, SEED);
            }, tris[indexMethode], 5, NOMBRE_MESURES};

            Resultats resultats = test.mesurer();

            // Rajoute l'entrée, avec le préfixe suivant (pour rendre plus joli sur excel)
            csv.ajouterEntree(nomsTris[indexMethode] + "," + std::to_string(tailleVecteur), resultats);
        }
    }

    return 0;
}