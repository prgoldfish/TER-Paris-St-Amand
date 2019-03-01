#ifndef REACTION_H
#define REACTION_H

#include <string>
#include "EspeceMoleculaire.h"

class Reaction
{
private:
    EspeceMoleculaire* reac1;
	EspeceMoleculaire* reac2;
	EspeceMoleculaire* produit1;
	EspeceMoleculaire* produit2;
	bool deuxReac;
	bool deuxProduit;
	float proba;
public:
    Reaction(EspeceMoleculaire* r1, EspeceMoleculaire* r2, EspeceMoleculaire* p1, EspeceMoleculaire* p2, bool dr, bool dp, float p);
    ~Reaction();
	EspeceMoleculaire* getReac1();
	EspeceMoleculaire* getReac2();
	EspeceMoleculaire* getProduit1();
	EspeceMoleculaire* getProduit2();
	bool get2Reac();
	bool get2Produits();
	float getProba();
};

#endif
