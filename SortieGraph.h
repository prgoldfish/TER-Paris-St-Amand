#ifndef SORTIEGRAPH_H
#define SORTIEGRAPH_H

#include <vector>
#include "EspeceMoleculaire.h"

class SortieGraph{
	private:
		std::vector<std::vector<double>>  courbes; // données des courbes
		std::vector<double> temps; // valeurs de temps correspondantes
		std::string * noms; // noms des courbes
		int tmax; // temps de fin du graphe
	public:
		SortieGraph(std::vector<EspeceMoleculaire*> especes, int tmax); // initialise le graphe avec les données de la situation initiale
		void ajouter(std::vector<double> valeurs); // ajoute des données au graphe et les affiche au fur à mesure
		void afficher(); // met le programme en pause pour afficher le graphe et attend que l'utilisateur le ferme
};

#endif