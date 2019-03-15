#include "EspeceMoleculaire.h"


EspeceMoleculaire::EspeceMoleculaire(std::string nom, int taille, float vitesse, int pop): nom(nom), taille(taille), vitesse(vitesse), pop(pop)
{
}

EspeceMoleculaire::EspeceMoleculaire(std::string nom): nom(nom)
{
}

EspeceMoleculaire::EspeceMoleculaire(): nom("")
{
}

EspeceMoleculaire::~EspeceMoleculaire()
{
}

std::string EspeceMoleculaire::getNom(){
	return nom;
}

int EspeceMoleculaire::getTaille(){
	return taille;
}

float EspeceMoleculaire::getVitesse(){
	return vitesse;
}

void EspeceMoleculaire::setTaille(int t){
	taille = t;
}

void EspeceMoleculaire::setVitesse(float v){
	vitesse = v;
}
