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
};
