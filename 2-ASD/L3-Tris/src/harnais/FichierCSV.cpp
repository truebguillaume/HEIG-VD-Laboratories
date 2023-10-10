//
// Created by ValentinRicard on 03.04.2023.
//

#include "FichierCSV.h"

FichierCSV::FichierCSV(const std::string &path, const std::string &header, size_t nb_mesures): out(std::ofstream(path)) {
    out << header;

    // Ajouter les identifiants de mesures:
    for (size_t i = 1; i < nb_mesures + 1; ++i) {
        out << "," << "mesureNo" << i;
    }

    out << std::endl;
}

void FichierCSV::ajouterEntree(const std::string &prefixe, const std::vector<unsigned long> &mesures) {
    // Ajouter le prefixe + les mesures :
    out << prefixe;

    for (const auto& mesure : mesures) {
        out << "," << mesure;
    }

    out << std::endl;
}
