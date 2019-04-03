#include "SortieGraph.h"

#define WITHOUT_NUMPY

#include "customPlot/matplotlibcpp.h"

namespace plt = matplotlibcpp;

SortieGraph::SortieGraph(std::vector<EspeceMoleculaire*> especes, int t){
	courbes.resize(especes.size() + 1);
	temps.push_back(0);
	for(unsigned int i = 0; i < especes.size(); i++) courbes[i].push_back(especes[i]->pop);
	courbes.back().push_back(0);
	tmax = t;
}

void SortieGraph::ajouter(std::vector<double> valeurs){
	temps.push_back(valeurs.front());
	plt::clf();
	plt::xlim(0, tmax);
	for(unsigned int i = 0; i < courbes.size(); i++){
		courbes[i].push_back(valeurs[i+1]);
		plt::plot(temps, courbes[i]);
	}
	plt::pause(0.001);
}

void SortieGraph::afficher(){
	plt::show();
}