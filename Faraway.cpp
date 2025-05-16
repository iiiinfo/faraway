#include "Structure.h"
#include "Calcul.h"
std::array<Region,68> ensR;
std::array<Sanctuaire,45> ensS;

int main() {
    ensR = loadRegions("Region.json");
    ensS = loadSanctuaires("Sanctuaire.json");
    // for(int i=0;i<68;i++) std::cout << ensR[i].carte << ": " << ensR[i].couleur << " " << ensR[i].nuit << " " << ensR[i].indice << " [" << ensR[i].merveilles[0] << ", " << ensR[i].merveilles[1] << ", " << ensR[i].merveilles[2] << "] " << ensR[i].score << " [" << ensR[i].score_par[0] << ", " << ensR[i].score_par[1] << "] " << " [" << ensR[i].condition[0] << ", " << ensR[i].condition[1] << ", " << ensR[i].condition[2] << "]" << std::endl;
    // for(int i=0;i<45;i++) std::cout << ensS[i].carte << ": " << ensS[i].couleur << " " << ensS[i].nuit << " " << ensS[i].indice << " [" << ensS[i].merveilles[0] << ", " << ensS[i].merveilles[1] << ", " << ensS[i].merveilles[2] << "] " << ensS[i].score << " [" << ensS[i].score_par[0] << ", " << ensS[i].score_par[1] << "] " << std::endl;
    instR regions;
    instS sanctuaires;
    tabR tabR;
    tabS tabS;
    std::string fic;
    std::cout << "Fichier : ";
    std::cin >> fic;
    lireinstance(fic,regions,sanctuaires);
    creationinstance(regions,sanctuaires,tabR,tabS);
    for(uint i=0;i<regions.size();i++) std::cout << regions[i] << " ";
    for(uint i=0;i<sanctuaires.size();i++) std::cout << sanctuaires[i] << " ";
    std::cout << std::endl;
    for(uint i=0;i<tabR.size();i++) std::cout << tabR[i].carte << ": " << tabR[i].couleur << " " << tabR[i].nuit << " " << tabR[i].indice << " [" << tabR[i].merveilles[0] << ", " << tabR[i].merveilles[1] << ", " << tabR[i].merveilles[2] << "] " << tabR[i].score << " [" << tabR[i].score_par[0] << ", " << tabR[i].score_par[1] << "] " << " [" << tabR[i].condition[0] << ", " << tabR[i].condition[1] << ", " << tabR[i].condition[2] << "]" << std::endl;
    for(uint i=0;i<tabS.size();i++) std::cout << tabS[i].carte << ": " << tabS[i].couleur << " " << tabS[i].nuit << " " << tabS[i].indice << " [" << tabS[i].merveilles[0] << ", " << tabS[i].merveilles[1] << ", " << tabS[i].merveilles[2] << "] " << tabS[i].score << " [" << tabS[i].score_par[0] << ", " << tabS[i].score_par[1] << "] " << std::endl;
}

// int main() {
//     instR regions;
//     instS sanctuaires;
//     tabR tabR;
//     tabS tabS;
//     std::string fic;
//     std::cout << "Fichier : ";
//     std::cin >> fic;
//     lireinstance(fic,regions,sanctuaires);
//     for(uint i=0;i<regions.size();i++) {
//         std::cout << regions[i] << " ";
//     }
//     for(uint i=0;i<sanctuaires.size();i++) {
//         std::cout << sanctuaires[i] << " ";
//     }
//     creationinstance(regions,sanctuaires,tabR,tabS);
//     std::cout << std::endl;
//     for(uint i=0;i<tabR.size();i++) {
//         std::cout << tabR[i].carte << ": " << tabR[i].couleur << " " << tabR[i].nuit << " " << tabR[i].indice << " [" << tabR[i].merveilles[0] << ", " << tabR[i].merveilles[1] << ", " << tabR[i].merveilles[2] << "] " << tabR[i].score << " [" << tabR[i].score_par[0] << ", " << tabR[i].score_par[1] << "] " << " [" << tabR[i].condition[0] << ", " << tabR[i].condition[1] << ", " << tabR[i].condition[2] << "]" << std::endl;
//     }
//     for(uint i=0;i<tabS.size();i++) {
//         std::cout << tabS[i].carte << ": " << tabS[i].couleur << " " << tabS[i].nuit << " " << tabS[i].indice << " [" << tabS[i].merveilles[0] << ", " << tabS[i].merveilles[1] << ", " << tabS[i].merveilles[2] << "] " << tabS[i].score << " [" << tabS[i].score_par[0] << ", " << tabS[i].score_par[1] << "] " << std::endl;
//     }
//     std::cout << std::endl << "Score : " << score(tabR,tabS);
// }