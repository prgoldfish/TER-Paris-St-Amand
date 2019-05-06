#include <cstdlib>
#include <cstdio>
#include <string>
#include "parser.tab.hpp"
#include "EspeceMoleculaire.h"
#include "Reaction.h"
#include "Simulation.h"
#include "SortieCSV.h"
#include "SortieGraph.h"

int diametre; // Diamètre de l'environnement (Une boule)
std::vector<EspeceMoleculaire*> especes; // Vecteur des espèces moléculaires disponibles
std::vector<Reaction*> reactions; // Vecteur des réactions disponibles
extern FILE *yyin; // Fichier à parser

int main(int argc, char** argv)
{
    int a = 2; // On traite les arguments par paquet de 2
    int skip = 1; // Nombre d'itérations requises pour mettre à jour l'affichage
    int nbIter = 100; // Nombre d'itérations
    bool fileDone = false, timeDone = false, simultypeDone = false, entiteCentree = false, jumpDone = false; // Pour savoir quels arguments ont étés réglés
    while (argc > a) 
    {
        if(std::string(argv[a - 1]) == "-f" && !fileDone) // Argument : -f nomFichier       Permet de spécifier le fichier à charger
        {
            yyin = fopen(argv[a], "r");
            fileDone = true;
        }
        else if(std::string(argv[a - 1]) == "-t" && !timeDone) // Argument : -t tempsEnµs   Spécifie le temps de simulation et le convertit en nombre d'itérations
        {
            nbIter = atoi(argv[a]) / 100;
            timeDone = true;
            if(nbIter < 1)
            {
               std::cout << "Temps invalide. Le temps doit etre d'au moins 100 µs." << std::endl;
               exit(0); 
            }
        }
        else if(std::string(argv[a - 1]) == "-j" && !jumpDone) // Argument : -j tempsEnµs   Spécifie le temps de simulation devant s'être écoulé pour mettre à jour l'affichage
        {
            skip = atoi(argv[a]) / 100;
            jumpDone = true;
            if(skip < 1)
            {
               std::cout << "Valeur de saut temporel invalide. Elle doit être supérieure ou égale à 100 µs. (La valeur est tronquée au 100 µs près)" << std::endl;
               exit(0); 
            }
        }
        else if(std::string(argv[a - 1]) == "-s" && !simultypeDone) // Argument : -s modeSimulation   Spécifie le mode de simulation
        {
            if(std::string(argv[a]) == "entiteCentre")
            {
                entiteCentree = true;
            }
            else if(std::string(argv[a]) == "simple")
            {
                entiteCentree = false;
            }
            else
            {
                std::cout << "Mode de simulation non reconnu. Modes disponibles : entiteCentre et simple" << std::endl;
                exit(0);
            }
            simultypeDone = true;
        }
        a += 2;
    }

    if(!fileDone)
    {
        std::cout << "Veuillez spécifier le fichier d'entrée avec l'option -f" << std::endl;
        exit(0);
    }
    


    yy::parser parser;
    parser.parse(); // On lit et interprète le fichier

    SortieCSV csv;
    csv.initFichier(especes); // Création du fichier CSV de sortie

    SortieGraph graph(especes, nbIter * 100); // Initialisation de l asortie graphique

    double temps = 0; //Temps en µs de simulation
    std::vector<double> resultats; // Vecteur contenant les résultats d'un pas de simulation
    Environnement env; // Environnement où les molécules interagissent (Utilisé en entité centré seulement)
    std::vector<Molecule *> listeMol = initSimulationEntitee(&env); // Création de la liste des molécules (Utilisé en entité centré seulement)

    bool sens = true; // Sens de lecture de la liste de molécules

        
    int s = 1; // Nombre d'itérations depuis la dernière mise à jour des résultats
    int nbReactions = 0;
    for(int j = 0; j < nbIter; j++) // Pour chaque itération
    {    
        if(entiteCentree) 
        {
            resultats = simulationEntiteeStep(temps, &env, listeMol, sens);
            sens = !sens; // Changement de sens
        }
        else // Population centré
        {
            resultats = simulationSimpleStep(temps);
        }

        nbReactions += resultats.back(); // on comte le nombre de collisions

        if(s >= skip) // Toutes les skip frames, on met à jour les résultat et l'affichage
        {
            s = 1;            
            resultats.pop_back();
            resultats.push_back(nbReactions); // On met le nombre de collisions depuis la dernière MaJ
            nbReactions = 0;
            csv.ajouter(resultats); //Ajout des résultats dans le fichier CSV
            graph.ajouter(resultats); //Ajout des résultats dans le ficgraphique
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
    graph.afficher(); // On affiche le graphe final

    return 0;
}