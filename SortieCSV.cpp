#include "SortieCSV.h"

int SortieCSV::initFichier(std::vector<EspeceMoleculaire*> especes){
	fichierCSV.open("resultat.csv", std::ios::trunc);
	//première ligne : noms des colonnes
	fichierCSV << "\"temps\""; //première colonne correspond au temps
    for(EspeceMoleculaire *e : especes) fichierCSV << ";\"" << e->getNom() << '"'; //liste des espèces séparées par des virgules et entourées de guillemets
	//deuxième ligne : situation initiale
	fichierCSV << std::endl << 0; //temps = 0
    for(EspeceMoleculaire *e : especes) fichierCSV << ';' << e->pop; //population de chaque espèce séparées par des virgules
	return 0;
}