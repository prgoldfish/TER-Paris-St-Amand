#ifndef SIMULATION_H
#define SIMULATION_H

#define _USE_MATH_DEFINES

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>
#include "EspeceMoleculaire.h"
#include "Reaction.h"

extern int diametre;
extern std::vector<EspeceMoleculaire*> especes;
extern std::vector<Reaction*> reactions; 

std::vector<double> simulationSimpleStep();
int getNbChocs(double proba, int nEm1, int nEm2, std::minstd_rand rng);
int getNbReacs(double proba, int nEm, std::minstd_rand rng);



#endif