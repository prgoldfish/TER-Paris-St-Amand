#include "SortieCSV.h"

void SortieCSV::initFichier(std::vector<EspeceMoleculaire*> especes) // Crée un fichier CSV pour y mettre les resultats
{
	fichierCSV.open("resultat.csv", std::ios::trunc); 
	// Première ligne : noms des colonnes
	fichierCSV << "\"temps\""; //La première colonne correspond au temps
    for(EspeceMoleculaire *e : especes) fichierCSV << ";\"" << e->getNom() << '"'; //La liste des espèces est séparée par des virgules et entourée de guillemets
	fichierCSV << ";\"reactions\""; //dernière colonne donne le nombre de réactions
	// Deuxième ligne : situation initiale
	fichierCSV << std::endl << 0; // temps = 0
    for(EspeceMoleculaire *e : especes) fichierCSV << ';' << e->pop; // Population de chaque espèce séparée par des virgules
	fichierCSV << ';' << 0; //pas encore de réaction
}

void SortieCSV::ajouter(std::vector<double> valeurs) // Ajoute une nouvelle ligne de valeurs
{
	bool premier = true;
	for(double v : valeurs)
	{
		if(premier)
		{
			// Ajouter une ligne
			premier = false;
			fichierCSV << std::endl;
			// Afficher le temps
			fichierCSV << (int) v;
		}
		else
		{
			// Ajouter une virgule
			fichierCSV << ';';
			// Ajouter la valeur
			fichierCSV << v;
		}
		
	}
}

void SortieCSV::fermerFichier() // Ferme le fichier CSV
{
	fichierCSV.close();
}