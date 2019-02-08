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
