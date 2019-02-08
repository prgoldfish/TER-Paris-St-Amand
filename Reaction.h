#include <string>
#include "EspeceMoleculaire.h"

class Reaction
{
private:
    EspeceMoleculaire* Reac1;
	EspeceMoleculaire* Reac2;
	EspeceMoleculaire* Produit1;
	EspeceMoleculaire* Produit2;
	float proba;
public:
    Reaction(EspeceMoleculaire* r1, EspeceMoleculaire* r2, EspeceMoleculaire* p1, EspeceMoleculaire* p2);
    ~Reaction();
};
