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
#include "Molecule.h"

extern int diametre;
extern std::vector<EspeceMoleculaire*> especes;
extern std::vector<Reaction*> reactions; 

std::vector<double> simulationSimpleStep(double time);
int getNbChocs(double proba, int nEm1, int nEm2, std::minstd_rand rng);
int getNbReacs(double proba, int nEm, std::minstd_rand rng);
std::vector<Molecule *> initSimulationEntitee(Environnement *env);
std::vector<double> simulationEntiteeStep(double time, Environnement *env, std::vector<Molecule *> &listeMolecules, bool sens);
bool collision(Molecule *m1, Molecule *m2);
Reaction* getReactionBi(Molecule *m1, Molecule *m2);
Reaction* getReactionMono(Molecule *m);
std::pair<Molecule*, Reaction *> checkCollisionsAndReac(Environnement *env, Molecule *m, std::minstd_rand rng, bool sens);
Reaction* checkReactionMono(Molecule *m, std::minstd_rand rng);




#endif