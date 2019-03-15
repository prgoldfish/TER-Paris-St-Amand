#ifndef SORTIECSV_H
#define SORTIECSV_H

#include <fstream>
#include <vector>
#include "EspeceMoleculaire.h"

class SortieCSV{
	private:
		std::ofstream fichierCSV;
	public:
		void initFichier(std::vector<EspeceMoleculaire*> especes);
		void ajouter(std::vector<double> valeurs);
		void fermerFichier();
};

#endif