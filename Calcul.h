#pragma once
#include "Structure.h"
#include <iostream>
#include <vector>
using tabR=std::vector<Region>;
using tabS=std::vector<Sanctuaire>;
using instR=std::vector<uint>;
using instS=std::vector<uint>;

uint nbsanctuaires(tabR ER);
uint min(uint a, uint b, uint c, uint d);
uint score(tabR ER, tabS ES);
void lireinstance(const std::string & filename, instR & regions, instS & sanctuaires);
void creationinstance(instR regions, instS sanctuaires, tabR & IR, tabS & IS);
void creationtableau(tabR IR, tabS IS, instR & regions, instS & sanctuaires);
void ecriretableau(std::string & filename, instR regions, instS sanctuaires);
liste totalconditions(tabR regions);
std::array<uint,10> totalscore_par(tabR regions);
std::array<uint,10> totalscore_par_sanctuaires(tabS sanctuaires);
std::array<uint,10> totalressources(tabR regions);
void switchr(Region & a, Region & b);
void switchs(Sanctuaire & a, Sanctuaire & b);
void switchui(int & a, int & b);
void tricroissant(tabR & regions);
void positions(tabR regions, tabS sanctuaires, std::vector<int> pos, std::vector<int> prio_sanc);
void positionnement(tabR & regions, std::vector<int> & pos);
tabS choix_sanc(uint nbsanc, tabS sanctuaires, std::vector<int> prio_sanc);