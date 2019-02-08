#include "EspeceMoleculaire.h"


EspeceMoleculaire::EspeceMoleculaire(std::string nom, int taille, float vitesse, int pop): nom(nom), taille(taille), vitesse(vitesse), pop(pop)
{
}

EspeceMoleculaire::EspeceMoleculaire(std::string nom): nom(nom)
{
}

EspeceMoleculaire::~EspeceMoleculaire()
{
}

void EspeceMoleculaire::setTaille(int t){
	taille = t;
}

void EspeceMoleculaire::setVitesse(float v){
	vitesse = v;
}

void EspeceMoleculaire::setPop(int p){
	pop = p;
}