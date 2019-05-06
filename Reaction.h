#ifndef REACTION_H
#define REACTION_H

#include <string>
#include "EspeceMoleculaire.h"

class Reaction
{
private:
    EspeceMoleculaire* reac1; // Premier réactif
	EspeceMoleculaire* reac2; // Second réactif
	EspeceMoleculaire* produit1; // Premier produit
	EspeceMoleculaire* produit2; // Second produit
	bool deuxReac; // Indique s'il y a 1 ou 2 reactifs
	bool deuxProduit; // Indique s'il y a 1 ou 2 produits
	float proba; // Probabilité que la réaction se produise
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
