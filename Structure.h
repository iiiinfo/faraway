#pragma once
#include <array>
#include <string>
#include "json/single_include/nlohmann/json.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;
using uint = unsigned int;
using liste = std::array<uint,3>; //pierre "p", chimère "chi", chardon "cha"

struct Region {
    uint carte;
    char couleur;
    bool nuit;
    bool indice;
    liste merveilles;
    uint score;
    std::array<uint,2> score_par; // pierre, chimère, chardon, carte nuit, indice, carte rouge, bleue, verte, et jaune, et ensemble (100 pour rien)
    liste condition;
};

struct Sanctuaire {
    uint carte;
    char couleur;
    bool nuit;
    bool indice;
    liste merveilles;
    uint score;
    std::array<uint,2> score_par; // pierre, chimère, chardon, carte nuit, indice, carte rouge, bleue, verte, et jaune, et ensemble (100 pour rien)
};

std::array<Region,68> loadRegions(const std::string & filename);
std::array<Sanctuaire,45> loadSanctuaires(const std::string & filename);

extern std::array<Region,68> ensR;
extern std::array<Sanctuaire,45> ensS;