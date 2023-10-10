//
// Created by ValentinRicard on 03.04.2023.
//

#ifndef ASD_LABOS_2021_FICHIERCSV_H
#define ASD_LABOS_2021_FICHIERCSV_H

#include <fstream>
#include <vector>

/**
 * Classe représentant un fichier CSV, facilitation la gestion du format.
 * Plutot que d'être typé en fonction des paramètre, un préfixe et un header est fourni, permettant
 * de personaliser le format à souhait.
 */
class FichierCSV {
private:
    /**
     * handle de fichier, permettant d'écrire dedans.
     */
    std::ofstream out;
public:
    /**
     * Crée un nouveau fichier CSV, écrasant le contenu pré-existant.
     * @param path Le chemin vers le fichier csv.
     * @param header Un header (ensemble de valeurs séparés par des virgules) pour la description de la mesure.
     * @param nb_mesures Le nombre de mesures effectuées par la classe TestPerformance.
     */
    FichierCSV(const std::string &path, const std::string &header, size_t nb_mesures);

    /**
     * Ajoute une nouvelle entrée (ligne) avec le préfixe et les mesures fournies.
     * @param prefixe Le préfixe (un ensemble de tags séparées par une virgule, pour le différencier des autres)
     * @param mesures Le vecteur des mesures effectuées.
     */
    void ajouterEntree(const std::string &prefixe, const std::vector<unsigned long> &mesures);
};


#endif //ASD_LABOS_2021_FICHIERCSV_H
