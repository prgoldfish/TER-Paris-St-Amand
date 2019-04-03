#include "SortieGraph.h"

#define WITHOUT_NUMPY

#include "customPlot/matplotlibcpp.h"

namespace plt = matplotlibcpp;

SortieGraph::SortieGraph(std::vector<EspeceMoleculaire*> especes){
	courbes.resize(especes.size());
}

void SortieGraph::ajouter(std::vector<double> valeurs){
	plt::clf();
	for(unsigned int i = 0; i < courbes.size(); i++){
		courbes[i].push_back(valeurs[i+1]);
		plt::plot(courbes[i]);
	}
	plt::pause(0.001);
}

void SortieGraph::afficher(){
	plt::show();
}