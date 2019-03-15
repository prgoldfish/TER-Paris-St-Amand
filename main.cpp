#include <cstdlib>
#include "parser.tab.hpp"
#include "EspeceMoleculaire.h"
#include "Reaction.h"
#include "SortieCSV.h"
#include "Simulation.h"

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
        std::cout << "\tPop : " << e->pop << std::endl << std::endl;
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

    std::cout << "Diametre : " << diametre << std::endl << std::endl;

    SortieCSV csv;
    csv.initFichier(especes);

    double temps = 0;
    std::vector<double> resultats;

    std::cout << "Après une étape : " << std::endl;

    for(int j = 0; j < 5000; j++)
    {    
        int i = 0;

        resultats = simulationSimpleStep(temps);

        for(double d : resultats) 
        {
            std::cout << "Col " << i << " : " << d << std::endl;
            i++;

        }

        csv.ajouter(resultats);

        temps = resultats.front();

        std::cout << std::endl << std::endl << std::endl;
    }

    csv.fermerFichier();

    return 0;
}