#include "Reaction.h"
#include "EspeceMoleculaire.h"


Reaction::Reaction(EspeceMoleculaire* r1, EspeceMoleculaire* r2, EspeceMoleculaire* p1, EspeceMoleculaire* p2, bool dr, bool dp, float p) // COnstructeur d'une réaction
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

EspeceMoleculaire* Reaction::getReac1()
{
	return reac1;
}

EspeceMoleculaire* Reaction::getReac2()
{
	return reac2;
}

EspeceMoleculaire* Reaction::getProduit1()
{
	return produit1;
}

EspeceMoleculaire* Reaction::getProduit2()
{
	return produit2;
}

bool Reaction::get2Reac()
{
	return deuxReac;
}

bool Reaction::get2Produits()
{
	return deuxProduit;
}

float Reaction::getProba()
{
	return proba;
}