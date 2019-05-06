#include "EspeceMoleculaire.h"

// Constructeurs
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

std::string EspeceMoleculaire::getNom() // Renvoie le nom
{
	return nom;
}

int EspeceMoleculaire::getTaille() // Renvoie la taille
{
	return taille;
}

float EspeceMoleculaire::getVitesse() // Renvoie la vitesse
{
	return vitesse;
}

void EspeceMoleculaire::setTaille(int t) // Met à jour la taille
{
	taille = t;
}

void EspeceMoleculaire::setVitesse(float v) // Met à jour la vitesse
{
	vitesse = v;
}
