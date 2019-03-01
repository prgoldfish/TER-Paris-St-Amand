#include "Reaction.h"
#include "EspeceMoleculaire.h"


Reaction::Reaction(EspeceMoleculaire* r1, EspeceMoleculaire* r2, EspeceMoleculaire* p1, EspeceMoleculaire* p2, bool dr, bool dp, float p)
{
	reac1 = r1;
	deuxReac = dr;
	if(dr) reac2 = r2;
	produit1 = p1;
	deuxProduit = dp;
	if(dp) produit2 = p2;
	proba = p;
}

Reaction::~Reaction()
{
}
