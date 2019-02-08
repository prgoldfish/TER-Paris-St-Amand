#include "Reaction.h"
#include "EspeceMoleculaire.h"


Reaction::Reaction(EspeceMoleculaire* r1, EspeceMoleculaire* r2, EspeceMoleculaire* p1, EspeceMoleculaire* p2) : Reac1(r1), Reac2(r2), Produit1(p1), Produit2(p2)
{
}

Reaction::~Reaction()
{
}
