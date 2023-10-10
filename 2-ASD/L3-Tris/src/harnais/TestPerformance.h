//
// Created by ValentinRicard on 21.03.2023.
//

#ifndef ASD2023_L3_TRIS_TESTPERFORMANCE_H
#define ASD2023_L3_TRIS_TESTPERFORMANCE_H

#include <functional>
#include <ctime>
#include <string>
#include <fstream>
#include <optional>
#include <cmath>
#include <chrono>

using Resultats = std::vector<unsigned long>;

template<typename IN>
class TestPerformance {
private:
    /**
     * Nombre d'exécutions de la fonction non comptées, avant de lancer les mesures
     */
    unsigned int toursDeChauffe = 5;
    /**
     * Nombre de mesures prises en compte dans le test
     */
    unsigned int nombreMesures = 25;
    /**
     * Un pointeur vers la fonction à tester
     */
    const std::function<void(IN)> &fonctionTestee;
    /**
     * Un pointer vers la fonction générant les données fournies à `fonctionTestee`
     */
    const std::function<IN()> &generatrice;
public:
    /**
     * Crée une nouvelle instance de `TestPerformance`, sans lancer les mesures
     * @param generatrice La fonction générant des données, fournies par génératrice.
     * @param fonctionTestee La fonction mesurée
     * @param toursDeChauffe Le nombre de tours de chauffe
     *                       (non mesurés, mais utilisés pour conditionner le cache du processeur)
     * @param nombreMesures Le nombre de mesures effectuées, et passées dans le vecteur résultats.
     */
    TestPerformance(const std::function<IN()> &generatrice,
                    const std::function<void(IN)> &fonctionTestee,
                    unsigned int toursDeChauffe = 5, unsigned int nombreMesures = 25) : toursDeChauffe(
            toursDeChauffe), nombreMesures(nombreMesures), fonctionTestee(fonctionTestee), generatrice(generatrice) {
    };

    /**
     * Lance les mesures, retournant le vecteur de résultats.
     * @return Un vecteur de résultats, de langueur `nombreMesures`
     */
    Resultats mesurer();
};

template<typename IN>
std::vector<unsigned long> TestPerformance<IN>::mesurer() {
    for (unsigned int chauffe = 0; chauffe < toursDeChauffe; ++chauffe) {
        IN valeur = generatrice();
        // On ne récupère pas l'entrée
        fonctionTestee(valeur);
    }

    std::vector<unsigned long> mesures;
    // On rentre dans les vraies valeurs :
    for (unsigned int mesureActuelle = 0; mesureActuelle < nombreMesures; ++mesureActuelle) {
        IN valeur = generatrice();
        auto start = std::chrono::high_resolution_clock::now();

        fonctionTestee(valeur);

        // On récupère l'instant de fin.
        auto stop = std::chrono::high_resolution_clock::now();

        // Récupère la durée de l'execution, en microsecondes.
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        mesures.push_back((unsigned long) duration.count());
    }

    return mesures;
}

#endif //ASD2023_L3_TRIS_TESTPERFORMANCE_H
