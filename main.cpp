#include <cstdlib>
#include "parser.tab.hpp"
#include "EspeceMoleculaire.h"
#include "Reaction.h"

int diametre;
std::vector<EspeceMoleculaire*> especes;
std::vector<Reaction*> reactions;

int main (int argc, char** argv)
{
    yy::parser parser;
    parser.parse();

    for(EspeceMoleculaire *e : especes)
    {
        std::cout << "Molecule : " << std::endl;
        std::cout << "\tNom : " << e->getNom() << std::endl;
        std::cout << "\tTaille : " << e->getTaille() << std::endl;
        std::cout << "\tVitesse : " << e->getVitesse() << std::endl;
        std::cout << "\tPop : " << e->getPop() << std::endl << std::endl;
    }

    std::cout << std::endl;

    for(Reaction *r : reactions)
    {
        std::cout << "Reaction : " << std::endl;
        std::cout << "\tMolecule 1 : " << r->getReac1()->getNom() << std::endl;
        if(r->get2Reac()) std::cout << "\tMolecule 2 : " << r->getReac2()->getNom() << std::endl;
        std::cout << "\tMolecule 3 : " << r->getProduit1()->getNom() << std::endl;
        if(r->get2Produits()) std::cout << "\tMolecule 4 : " << r->getProduit2()->getNom() << std::endl << std::endl;
        std::cout << "\tProba : " << r->getProba() << std::endl << std::endl;
    }

    std::cout << "\tDiametre : " << diametre << std::endl << std::endl;

    return 0;
}