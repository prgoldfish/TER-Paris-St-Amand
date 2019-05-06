#include "SortieGraph.h"

#include "customPlot/matplotlibcpp.h"

namespace plt = matplotlibcpp;

SortieGraph::SortieGraph(std::vector<EspeceMoleculaire*> especes, int t)
{
	courbes.resize(especes.size() + 1); // 1 courbe par espèce + 1 courbe pour le nombre de réactions
	temps.push_back(0); // Le temps commence à 0
	noms = new std::string[especes.size() + 1];
	for(unsigned int i = 0; i < especes.size(); i++)
	{
		courbes[i].push_back(especes[i]->pop); // Ajoute les données initiales
		noms[i] = especes[i]->getNom(); // Ajoute le nom des molécules à la légende
	}
	courbes.back().push_back(0); // Il n'y a pas encore de réaction
	noms[especes.size()] = "Reactions"; // Ajoute les réactions à la légende
	tmax = t;
}

void SortieGraph::ajouter(std::vector<double> valeurs)
{
	temps.push_back(valeurs.front()); // Ajoute le temps des nouvelles données
	plt::clf(); // Efface le graphe précédent pour le remplacer
	plt::xlim(0, tmax); // l'axe X va du début à la fin de la simulation
	double max = 0;
	for(unsigned int i = 0; i < courbes.size(); i++) // Pour chaque courbe
	{
		courbes[i].push_back(valeurs[i+1]); // On ajoute la nouvelle valeur
		// Calcul de la valeur max pour ajuster l'échelle
		for(unsigned int j = 0; j < courbes[i].size(); j++)
		{
			if(courbes[i][j] > max) max = courbes[i][j];
		}
		plt::named_plot(noms[i], temps, courbes[i]); // Trace la courbe
	}
	plt::legend(); // Ajoute la légende
	plt::ylim((int) (max * -0.01), (int) (max * 1.01)); // Ajuste l'échelle en fonction de max (avec 1/100 d'écart pour empêcher les bords de couvrir des portions de courbes)
	plt::pause(0.00001); // Affiche les nouvelles courbes
}

void SortieGraph::afficher() // Affiche le graphe
{
	plt::show();
}