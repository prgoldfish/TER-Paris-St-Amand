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


#endif