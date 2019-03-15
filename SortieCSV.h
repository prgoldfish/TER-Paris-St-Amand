#ifndef SORTIECSV_H
#define SORTIECSV_H

#include <fstream>
#include <vector>
#include "EspeceMoleculaire.h"

class SortieCSV{
	private:
		std::ofstream fichierCSV;
	public:
		int initFichier(std::vector<EspeceMoleculaire*> especes);
};

#endif