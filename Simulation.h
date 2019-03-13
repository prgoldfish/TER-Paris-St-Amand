#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "EspeceMoleculaire.h"
#include "Reaction.h"

extern int diametre;
extern std::vector<EspeceMoleculaire*> especes;
extern std::vector<Reaction*> reactions; 

std::vector<double> simulationSimpleStep();


#endif