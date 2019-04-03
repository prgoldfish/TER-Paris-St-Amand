#ifndef SORTIEGRAPH_H
#define SORTIEGRAPH_H

#include <vector>
#include "EspeceMoleculaire.h"

class SortieGraph{
	private:
		std::vector<std::vector<double>>  courbes;
		std::vector<double> temps;
	public:
		SortieGraph(std::vector<EspeceMoleculaire*> especes);
		void ajouter(std::vector<double> valeurs);
		void afficher();
};

#endif