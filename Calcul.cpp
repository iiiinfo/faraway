#include "Calcul.h"
/* Calcul de position:
Prendre en compte les valeurs d'une carte:
nombre de ressources, conditions etc
Et déduire à partir de ça une valeur "priorité" qui nous dit
que devrait être la position de la carte
*/

uint nbsanctuaires(tabR ER) {
    uint nb=0;
    for(uint i=0;i<ER.size()-1;i++) {
        if(ER[i+1].carte>ER[i].carte) nb++;
    }
    return nb;
}

uint min(uint a, uint b, uint c, uint d) {
    uint min=a;
    if(b<min) min=b;
    if(c<min) min=c;
    if(d<min) min=d;
    return min;
}

uint score(tabR ER, tabS ES) {
    uint sc=0;
    std::array<uint,10> total; // pierre, chimère, chardon, carte nuit, indice, carte rouge, bleue, verte, et jaune, et ensemble
    for(int i=0;i<10;i++) {
        total[i]=0;
    }
    for(uint i=0;i<ES.size();i++) {
        if(ES[i].couleur=='r') total[5]++;
        if(ES[i].couleur=='b') total[6]++;
        if(ES[i].couleur=='v') total[7]++;
        if(ES[i].couleur=='j') total[8]++;
        if(ES[i].nuit) total[3]++;
        if(ES[i].indice) total[4]++;
        total[9]=min(total[5],total[6],total[7],total[8]);
        total[0]+=ES[i].merveilles[0];
        total[1]+=ES[i].merveilles[1];
        total[2]+=ES[i].merveilles[2];
    }
    for(int i=ER.size()-1;i>=0;i--) {
        if(ER[i].couleur=='r') total[5]++;
        if(ER[i].couleur=='b') total[6]++;
        if(ER[i].couleur=='v') total[7]++;
        if(ER[i].couleur=='j') total[8]++;
        if(ER[i].nuit) total[3]++;
        if(ER[i].indice) total[4]++;
        total[9]=min(total[5],total[6],total[7],total[8]);
        total[0]+=ER[i].merveilles[0];
        total[1]+=ER[i].merveilles[1];
        total[2]+=ER[i].merveilles[2];
        if(total[0]>=ER[i].condition[0] && total[1]>=ER[i].condition[1] && total[2]>=ER[i].condition[2]) {
            if(ER[i].score_par[0]==100 && ER[i].score_par[1]==100) sc+=ER[i].score;
            else {
                if(ER[i].score_par[1]==100) sc+=ER[i].score*total[ER[i].score_par[0]];
                else sc+=ER[i].score*(total[ER[i].score_par[0]]+total[ER[i].score_par[1]]);
            }
        }
    }
    for(uint i=0;i<ES.size();i++) {
        if(ES[i].score_par[0]==100 && ES[i].score_par[1]==100) sc+=ES[i].score;
        else {
            if(ES[i].score_par[1]==100) sc+=ES[i].score*total[ES[i].score_par[0]];
            else sc+=ES[i].score*(total[ES[i].score_par[0]]+total[ES[i].score_par[1]]);
        }
    }
    return sc;
}

void lireinstance(const std::string & filename, instR & regions, instS & sanctuaires) {
    std::ifstream f(filename);
    if(f.is_open()) {
        uint v;
        while(f.good()) {
            f >> v;
            if(v<=68) regions.push_back(v);
            else sanctuaires.push_back(v);
        }
        f.close();
    }
    else std::cout << "Le fichier " << filename << " n'a pas été trouvé.";
}

void creationinstance(instR regions, instS sanctuaires, tabR & IR, tabS & IS) {
    std::array<Region,68> ensR;
    std::array<Sanctuaire,45> ensS;
    ensR = loadRegions("Region.json");
    ensS = loadSanctuaires("Sanctuaire.json");
    for(uint i=0;i<regions.size();i++) {
        IR.push_back(ensR[regions[i]-1]);
    }
    for(uint i=0;i<sanctuaires.size();i++) {
        IS.push_back(ensS[sanctuaires[i]-101]);
    }
}

void creationtableau(tabR IR, tabS IS, instR & regions, instS & sanctuaires) {
    for(uint i=0;i<IR.size();i++) {
        regions.push_back(IR[i].carte);
    }
    for(uint i=0;i<IS.size();i++) {
        sanctuaires.push_back(IS[i].carte);
    }
} 

void ecriretableau(std::string & filename, instR regions, instS sanctuaires) {
    std::ofstream f(filename);
    if(f.is_open()) {
        for(uint i=0;i<regions.size();i++) {
            f << regions[i];
            f << " ";
        }
        for(uint i=0;i<sanctuaires.size();i++) {
            f << sanctuaires[i];
            f << " ";
        }
        f.close();
    }
}

liste totalconditions(tabR regions) {
    liste total;
    total[0]=0;
    total[1]=0;
    total[2]=0;
    for(uint i=0;i<regions.size();i++) {
        total[0]+=regions[i].condition[0];
        total[1]+=regions[i].condition[1];
        total[2]+=regions[i].condition[2];
    }
    return total;
}

std::array<uint,10> totalscore_par(tabR regions) {
    std::array<uint,10> total;
    for(uint i=0;i<10;i++) total[i]=0;
    for(uint i=0;i<regions.size();i++) {
        if(regions[i].score_par[0]!=100 && regions[i].score_par[1]!=100) {
            total[regions[i].score_par[0]]+=regions[i].score;
            total[regions[i].score_par[1]]+=regions[i].score;
        }
        else if(regions[i].score_par[0]!=100) total[regions[i].score_par[0]]+=regions[i].score;
    }
    return total;
}

std::array<uint,10> totalscore_par_sanctuaires(tabS sanctuaires) {
    std::array<uint,10> total;
    for(uint i=0;i<10;i++) total[i]=0;
    for(uint i=0;i<sanctuaires.size();i++) {
        if(sanctuaires[i].score_par[0]!=100 && sanctuaires[i].score_par[1]!=100) {
            total[sanctuaires[i].score_par[0]]+=sanctuaires[i].score;
            total[sanctuaires[i].score_par[1]]+=sanctuaires[i].score;
        }
        else if(sanctuaires[i].score_par[0]!=100) total[sanctuaires[i].score_par[0]]+=sanctuaires[i].score;
    }
    return total;
}

std::array<uint,10> totalressources(tabR regions) {
    std::array<uint,10> total; // pierre, chimère, chardon, carte nuit, indice, carte rouge, bleue, verte, et jaune, et ensemble
    for(int i=0;i<10;i++) {
        total[i]=0;
    }
    for(uint i=0;i<regions.size();i++) {
        if(regions[i].couleur=='r') total[5]++;
        if(regions[i].couleur=='b') total[6]++;
        if(regions[i].couleur=='v') total[7]++;
        if(regions[i].couleur=='j') total[8]++;
        if(regions[i].nuit) total[3]++;
        if(regions[i].indice) total[4]++;
        total[9]=min(total[5],total[6],total[7],total[8]);
        total[0]+=regions[i].merveilles[0];
        total[1]+=regions[i].merveilles[1];
        total[2]+=regions[i].merveilles[2];
    }
    return total;
}

void switchr(Region & a, Region & b) {
    Region c=a;
    a=b;
    b=c;
}

void switchs(Sanctuaire & a, Sanctuaire & b) {
    Sanctuaire c=a;
    a=b;
    b=c;
}

void switchui(int & a, int & b) {
    int c=a;
    a=b;
    b=c;
}

void tricroissant(tabR & regions) {
    uint min;
    for(uint i=0;i<regions.size();i++) {
        min=i;
        for(uint j=i;j<regions.size();j++) {
            if(regions[j].carte<regions[min].carte) min=j;
        }
        switchr(regions[i],regions[min]);
    }
}

void positions(tabR regions, tabS sanctuaires, std::vector<int> pos, std::vector<int> prio_sanc) {
    int ordre=0;
    for(uint i=0;i<8;i++) pos.push_back(0);
    for(uint i=0;i<sanctuaires.size();i++) prio_sanc.push_back(0);
    for(uint i=0;i<8;i++) {
        if(regions[i].score_par[0]==100) pos[i]+=regions[i].score;
        for(uint j=0;j<8;j++) {
            if(j!=i) {
                if((regions[j].score_par[0]==5 || regions[j].score_par[1]==5) && regions[i].couleur=='r') {
                    pos[i]+=regions[j].score;
                    pos[j]-=regions[j].score;
                }
                if((regions[j].score_par[0]==6 || regions[j].score_par[1]==6) && regions[i].couleur=='b') {
                    pos[i]+=regions[j].score;
                    pos[j]-=regions[j].score;
                }
                if((regions[j].score_par[0]==7 || regions[j].score_par[1]==7) && regions[i].couleur=='v') {
                    pos[i]+=regions[j].score;
                    pos[j]-=regions[j].score;
                }
                if((regions[j].score_par[0]==8 || regions[j].score_par[1]==8) && regions[i].couleur=='j') {
                    pos[i]+=regions[j].score;
                    pos[j]-=regions[j].score;
                }
                if(regions[j].score_par[0]==0) {
                    pos[i]+=regions[j].score*regions[i].merveilles[0];
                    pos[j]-=regions[j].score*regions[i].merveilles[0];
                }
                if(regions[j].score_par[0]==1) {
                    pos[i]+=regions[j].score*regions[i].merveilles[1];
                    pos[j]-=regions[j].score*regions[i].merveilles[1];
                }
                if(regions[j].score_par[0]==2) {
                    pos[i]+=regions[j].score*regions[i].merveilles[2];
                    pos[j]-=regions[j].score*regions[i].merveilles[2];
                }
                if(regions[j].score_par[0]==3) {
                    pos[i]+=regions[j].score*regions[i].nuit;
                    pos[j]-=regions[j].score*regions[i].nuit;
                }
                if(regions[j].score_par[0]==4) {
                    pos[i]+=regions[j].score*regions[i].indice;
                    pos[j]-=regions[j].score*regions[i].indice;
                }
                if(regions[j].score_par[0]==9) { // A améliorer
                    // std::array<uint,4> ens[j];
                    pos[i]+=regions[j].score;
                    pos[j]-=regions[j].score;
                }
                if(regions[j].condition[0]==0) {
                    pos[i]+=regions[j].score*regions[i].merveilles[0];
                    pos[j]-=regions[j].score*regions[i].merveilles[0];
                }
                if(regions[j].condition[0]==1) {
                    pos[i]+=regions[j].score*regions[i].merveilles[1];
                    pos[j]-=regions[j].score*regions[i].merveilles[1];
                }
                if(regions[j].condition[0]==2) {
                    pos[i]+=regions[j].score*regions[i].merveilles[2];
                    pos[j]-=regions[j].score*regions[i].merveilles[2];
                }
            }
        }
        for(uint j=0;j<sanctuaires.size();j++) {
            if((sanctuaires[j].score_par[0]==5 || sanctuaires[j].score_par[1]==5) && regions[i].couleur=='r') {
                prio_sanc[j]+=sanctuaires[j].score;
                ordre+=sanctuaires[j].score;
            } 
            if((sanctuaires[j].score_par[0]==6 || sanctuaires[j].score_par[1]==6) && regions[i].couleur=='b') {
                prio_sanc[j]+=sanctuaires[j].score;
                ordre+=sanctuaires[j].score;
            }
            if((sanctuaires[j].score_par[0]==7 || sanctuaires[j].score_par[1]==7) && regions[i].couleur=='v') {
                prio_sanc[j]+=sanctuaires[j].score;
                ordre+=sanctuaires[j].score;
            }
            if((sanctuaires[j].score_par[0]==8 || sanctuaires[j].score_par[1]==8) && regions[i].couleur=='j') {
                prio_sanc[j]+=sanctuaires[j].score;
                ordre+=sanctuaires[j].score;
            }
            if(sanctuaires[j].score_par[0]==0) {
                prio_sanc[j]+=sanctuaires[j].score*regions[i].merveilles[0];
                ordre+=sanctuaires[j].score*regions[i].merveilles[0];
            }
            if(sanctuaires[j].score_par[0]==1) {
                prio_sanc[j]+=sanctuaires[j].score*regions[i].merveilles[1];
                ordre+=sanctuaires[j].score*regions[i].merveilles[1];
            }
            if(sanctuaires[j].score_par[0]==2) {
                prio_sanc[j]+=sanctuaires[j].score*regions[i].merveilles[2];
                ordre+=sanctuaires[j].score*regions[i].merveilles[2];
            }
            if(sanctuaires[j].score_par[0]==3) {
                prio_sanc[j]+=sanctuaires[j].score*regions[i].nuit;
                ordre+=sanctuaires[j].score*regions[i].nuit;
            }
            if(sanctuaires[j].score_par[0]==4) {
                prio_sanc[j]+=sanctuaires[j].score*regions[i].indice;
                ordre+=sanctuaires[j].score*regions[i].indice;
            }
        }
    }
    for(uint i=1;i<8;i++) { // Importance des cartes sanctuaires: ajout d'un poids pour la croissance des numéros
        pos[i]+=ordre*i;
    }
}

tabR positionnement(tabR regions, std::vector<int> pos) {
    uint min;
    for(uint i=0;i<pos.size();i++) {
        min=i;
        for(uint j=i;j<pos.size();j++) {
            if(pos[j]<pos[i]) min=j;
        }
        switchr(regions[min],regions[i]);
        switchui(pos[min],pos[i]);
    }
    return regions;
}

tabS choix_sanc(uint nbsanc, tabS sanctuaires, std::vector<int> prio_sanc) {
    uint max;
    tabS S;
    for(uint i=0;i<nbsanc;i++) {
        max=i;
        for(uint j=i;j<prio_sanc.size();j++) {
            if(prio_sanc[j]>prio_sanc[i]) max=j;
        }
        S.push_back(sanctuaires[max]);
        switchs(sanctuaires[max],sanctuaires[i]);
        switchui(prio_sanc[max],prio_sanc[i]);
    } 
}

/** Idées:
 * Récurrence ?
 * Stratégies se basant sur une caractéristique ou deux (indices, cartes nuit etc)
 * Apprentissage: Soit x le réajustement que l'on rajoute à la valeur et on rajoute des coefficients; ax+b, ax²+bx+c ou même ax^3+bx²+cx+d
 * Calcul de position basé sur les informations des cartes
 */