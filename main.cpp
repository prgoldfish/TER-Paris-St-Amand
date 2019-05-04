#include <cstdlib>
#include <cstdio>
#include <string>
#include "parser.tab.hpp"
#include "EspeceMoleculaire.h"
#include "Reaction.h"
#include "Simulation.h"
#include "SortieCSV.h"
#include "SortieGraph.h"

int diametre;
std::vector<EspeceMoleculaire*> especes;
std::vector<Reaction*> reactions;
extern FILE *yyin;

int main (int argc, char** argv)
{
    int a = 2;
    int skip = 1;
    int nbIter = 100;
    bool fileDone = false, timeDone = false, simultypeDone = false, entiteCentree = false, jumpDone = false;
    while (argc > a) 
    {
        if(std::string(argv[a - 1]) == "-f" && !fileDone)
        {
            yyin = fopen(argv[a], "r");
            fileDone = true;
        }
        else if(std::string(argv[a - 1]) == "-t" && !timeDone)
        {
            nbIter = atoi(argv[a]) / 100;
            timeDone = true;
            if(nbIter < 1)
            {
               std::cout << "Temps invalide. Le temps doit etre d'au moins 100 µs." << std::endl;
               exit(0); 
            }
        }
        else if(std::string(argv[a - 1]) == "-j" && !jumpDone)
        {
            skip = atoi(argv[a]) / 100;
            jumpDone = true;
            if(skip < 1)
            {
               std::cout << "Valeur de saut temporel invalide. Elle doit être supérieure ou égale à 100 µs. (La valeur est tronquée au 100 µs près)" << std::endl;
               exit(0); 
            }
        }
        else if(std::string(argv[a - 1]) == "-s" && !simultypeDone)
        {
            if(std::string(argv[a]) == "entiteCentree")
            {
                entiteCentree = true;
            }
            else if(std::string(argv[a]) == "simple")
            {
                entiteCentree = false;
            }
            else
            {
                std::cout << "Mode de simulation non reconnu. Modes disponibles : entiteCentree et simple" << std::endl;
                exit(0);
            }
            simultypeDone = true;
        }
        a += 2;
    }
    


    yy::parser parser;
    parser.parse();

    /*for(EspeceMoleculaire *e : especes)
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
*/
    SortieCSV csv;
    csv.initFichier(especes);

    SortieGraph graph(especes, nbIter * 100);

    double temps = 0;
    std::vector<double> resultats;
    Environnement env;
    std::vector<Molecule *> listeMol = initSimulationEntitee(&env);
    /*std::cout << "Nombre de molécules : " << listeMol.size() << std::endl;
    
    for(Molecule m : listeMol)
    {
        std::cout << "Molecule : " << std::endl;
        std::cout << "\tX : " << m.getX() << std::endl;
        std::cout << "\tY : " <<m.getY() << std::endl;
        std::cout << "\tZ : " << m.getZ() << std::endl;
        std::cout << "\tEspèce : " << m.getEspece()->getNom() << std::endl << std::endl;
    }

    
    std::cout << "Liste de molécules : " << env.findMolecule(&(listeMol[0]))->size() << std::endl; */
    int sum = 0;
    for(int i = 0; i < env.cubeSize(); i++)
    {
        for(int j = 0; j < env.cubeSize(); j++)
        {
            for(int k = 0; k < env.cubeSize(); k++)
            {
                sum += env.getListIndices(i, j, k).size();
            }
        }
    }
    
    
    std::cout << "NB Mol : " << sum << std::endl;

    std::vector<Molecule*> listMol = env.findMolecule(listeMol[0]);
    for(size_t molI = 0; molI < listMol.size(); molI++) 
    {
        std::cout << listMol.at(molI) << std::endl;
        std::cout << listMol.at(molI)->getEspece()->getNom() << std::endl;
    }
    std::cout << listeMol[0] << std::endl;
    

    bool sens = true;


    std::cout << "Après une étape : " << std::endl;
    std::cout << "Taille cube : " << env.cubeSize() << std::endl;
        
    int s = 1;
    int nbCollisions = 0;
    for(int j = 0; j < nbIter; j++)
    {    
        if(entiteCentree)
        {
            resultats = simulationEntiteeStep(temps, &env, listeMol, sens);
            sens = !sens;
            //std::cout << "endStep" << std::endl;
        }
        else
        {
            resultats = simulationSimpleStep(temps);
        }

        nbCollisions += resultats.back();

        if(s >= skip)
        {
            int i = 0;
            s = 1;
            
            resultats.pop_back();
            resultats.push_back(nbCollisions);
            nbCollisions = 0;

            /*for(double d : resultats) 
            {
                std::cout << "Col " << i << " : " << d << std::endl;
                i++;

            }
            std::cout << std::endl << std::endl << std::endl;
            */
            csv.ajouter(resultats);
            graph.ajouter(resultats);
        }
        else
        {
            s++;
        }
        temps = resultats.front();
    }

    for(auto&& e : especes)
    {
        delete e;
    }

    for(auto&& r : reactions)
    {
        delete r;
    }

    for(auto&& mol : listeMol)
    {
        delete mol;
    }

    csv.fermerFichier();
    graph.afficher();

    return 0;
}