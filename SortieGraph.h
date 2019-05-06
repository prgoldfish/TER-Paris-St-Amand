#ifndef SORTIEGRAPH_H
#define SORTIEGRAPH_H

#include <vector>
#include "EspeceMoleculaire.h"

class SortieGraph{
	private:
		std::vector<std::vector<double>> courbes; // Données des courbes
		std::vector<double> temps; // Valeurs de temps correspondantes
		std::string *noms; // Noms des courbes
		int tmax; // Temps de fin du graphe
	public:
		SortieGraph(std::vector<EspeceMoleculaire*> especes, int tmax); // Initialise le graphe avec les données de la situation initiale
		void ajouter(std::vector<double> valeurs); // Ajoute des données au graphe et les affiche au fur à mesure
		void afficher(); // Met le programme en pause pour afficher le graphe et attend que l'utilisateur le ferme
};

#endif