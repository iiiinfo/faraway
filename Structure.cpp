#include "Structure.h"

std::array<Region,68> loadRegions(const std::string & filename) {
    std::ifstream file(filename);
    json j;
    file >> j;
    std::array<Region,68> regions;
    for (size_t i = 0; i < regions.size(); ++i) {
        const auto& item = j.at(i);
        regions[i].carte = item.at("carte").get<uint>();
        regions[i].couleur = item.at("couleur").get<std::string>()[0];
        regions[i].nuit = item.at("nuit").get<int>();
        regions[i].indice = item.at("indice").get<int>();
        regions[i].merveilles = item.at("merveilles").get<liste>();
        regions[i].score = item.at("score").get<uint>();
        regions[i].score_par = item.at("score_par").get<std::array<uint,2>>();
        regions[i].condition = item.at("condition").get<liste>();
    }
    return regions;
}

std::array<Sanctuaire,45> loadSanctuaires(const std::string & filename) {
    std::ifstream file(filename);
    json j;
    file >> j;
    std::array<Sanctuaire,45> sanctuaire;
    for (size_t i = 0; i < sanctuaire.size(); ++i) {
        const auto& item = j.at(i);
        sanctuaire[i].carte = item.at("carte").get<uint>();
        sanctuaire[i].couleur = item.at("couleur").get<std::string>()[0];
        sanctuaire[i].nuit = item.at("nuit").get<int>();
        sanctuaire[i].indice = item.at("indice").get<int>();
        sanctuaire[i].merveilles = item.at("merveilles").get<liste>();
        sanctuaire[i].score = item.at("score").get<uint>();
        sanctuaire[i].score_par = item.at("score_par").get<std::array<uint,2>>();
   
    }
    return sanctuaire;
}