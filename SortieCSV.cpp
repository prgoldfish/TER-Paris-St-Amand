#include "SortieCSV.h"

void SortieCSV::initFichier(std::vector<EspeceMoleculaire*> especes){
	fichierCSV.open("resultat.csv", std::ios::trunc);
	//première ligne : noms des colonnes
	fichierCSV << "\"temps\""; //première colonne correspond au temps
    for(EspeceMoleculaire *e : especes) fichierCSV << ";\"" << e->getNom() << '"'; //liste des espèces séparées par des virgules et entourées de guillemets
	fichierCSV << ";\"nombre de collisions\""; //dernière colonne donne le nombre de collisions
	//deuxième ligne : situation initiale
	fichierCSV << std::endl << 0; //temps = 0
    for(EspeceMoleculaire *e : especes) fichierCSV << ';' << e->pop; //population de chaque espèce séparées par des virgules
	fichierCSV << ';' << 0; //pas encore de collision
}

void SortieCSV::ajouter(std::vector<double> valeurs){
	bool premier = true;
	for(double v : valeurs){
		if(premier){
			//ajouter une ligne
			premier = false;
			fichierCSV << std::endl;
			//afficher le temps
			fichierCSV << (int) v;
		}else{
			//ajouter une virgule
			fichierCSV << ';';
			//ajouter la valeur
			fichierCSV << v;
		}
		
	}
}

void SortieCSV::fermerFichier(){
	fichierCSV.close();
}