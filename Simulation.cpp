#include "Simulation.h"
#include <iostream>

std::vector<double> simulationSimpleStep(double time) // Fait une étape de simulation population centré
{
	std::vector<double> results; // Vecteur de résultats
	std::minstd_rand generator(std::chrono::system_clock::now().time_since_epoch().count()); // Initialisation du générateur de nombres aléatoires
	std::shuffle(reactions.begin(), reactions.end(), generator); // Mélange du vecteur de réactions

	results.push_back(time + 100);
	int nbReactions = 0;

	for(Reaction *r : reactions) // Pour chaque réaction qui existe
	{
		if(r->get2Reac()) //Si c'est bi-moléculaire
		{
			int nbChocs = getNbChocs(r->getProba(), r->getReac1()->pop, r->getReac2()->pop, generator); // On récupère le nombre de réactions
			
			// On met à jour la population de molécules
			r->getReac1()->pop -= nbChocs;
			r->getReac2()->pop -= nbChocs;
			r->getProduit1()->pop += nbChocs;
			if(r->get2Produits())
			{
				r->getProduit2()->pop += nbChocs;
			}
			nbReactions += nbChocs;
		}
		else //Si c'est mono-moléculaire
		{
			int nbReacs = getNbReacs(r->getProba(), r->getReac1()->pop, generator); // On récupère le nombre de réactions
			
			// On met à jour la population de molécules
			r->getReac1()->pop -= nbReacs;
			r->getProduit1()->pop += nbReacs;
			if(r->get2Produits())
			{
				r->getProduit2()->pop += nbReacs;
			}
			nbReactions += nbReacs;

		}
	}

	for(EspeceMoleculaire *e : especes)
    {
        results.push_back(e->pop); // On remplit le vecteur de résulats
    }

	results.push_back((double) nbReactions); // On ajoute le nombre de réactions 

	return results;
}


int getNbChocs(double proba, int nEm1, int nEm2, std::minstd_rand rng) // Donne le nombre de chocs entre 2 populations de molécules
{
	double alpha = 7.4e-7;
	double volume = 4.0 * (M_PI / 3.0) *  pow((double) diametre * 1e-3 / 2, 3.0); // Calcul du volume
	double nb = proba * alpha * nEm1 * nEm2 / volume; // Nombre de chocs
	int nbChocs = (int) nb;
	double decPart = nb - nbChocs;
	std::uniform_real_distribution<double> distribution(0.0,1.0);
	if(distribution(rng) < decPart) // On arrondit aléatoirement le nombre de chocs
	{
		nbChocs++;
	}
	return nbChocs;
}

int getNbReacs(double proba, int nEm, std::minstd_rand rng) // Donne le nombre de réactions dans une population de molécules
{
	double nb = proba * nEm; // Nombre de réactions
	int nbReacs = (int) nb;
	double decPart = nb - nbReacs;
	std::uniform_real_distribution<double> distribution(0.0,1.0);
	if(distribution(rng) < decPart) // On arrondit aléatoirement le nombre de chocs
	{
		nbReacs++;
	}
	return nbReacs;
}

std::vector<Molecule *> initSimulationEntitee(Environnement *env) // Crée les molécules pour la simulation entité centrée 
{
	std::vector<Molecule *> listeMolecules;
	for(auto&& e : especes)
	{
		for(int i = 0; i < e->pop; i++)
		{
			Molecule *m = new Molecule(e); // Sa position est aléatoire
			listeMolecules.push_back(m);
			env->ajoutMolecule(m);
		}
	}
	return listeMolecules;
}

// Effectue un pas de simulation entitée centrée
std::vector<double> simulationEntiteeStep(double time, Environnement *env, std::vector<Molecule *> &listeMolecules, bool sens) //true pour debut->fin et false pour fin->debut 
{
	std::minstd_rand generator(std::chrono::system_clock::now().time_since_epoch().count()); // Initialisation du moteur de génération de nombres aléatoires
	std::shuffle(reactions.begin(), reactions.end(), generator); // On mélange la liste des réactions
	
	std::vector<double> results;
	results.push_back(time + 100);

	std::vector<Molecule *> listeMoleculesMaj; // Nouvelle liste de molécules
	
	int nbReactions = 0;
	int nbMol = listeMolecules.size(); // Nombre de molécules à traiter

	std::vector<Molecule *> aSuppr; // Liste des molécule à delete

	int i = (sens ? 0 : nbMol - 1);
	for(; sens ? (i < nbMol) : (i >= 0); sens ? i++ : i--) // Boucle for à double sens
	{
		Molecule *m = listeMolecules.at(i);
		if(m->traitee == sens) // Si la molécule est déjà traitée
		{
			continue; // On l'ignore
		}
		if(!m->move(env)) // Si la molécule n'a pas pu bouger
		{
			m->traitee = sens; 
			if(sens) // Le sens d'insertion dans la nouvelle liste change en fonction du sens de lecture
			{
				listeMoleculesMaj.push_back(m);
			}
			else
			{
				listeMoleculesMaj.insert(listeMoleculesMaj.begin(), m);
			}
			continue;
		}

		std::pair<Molecule *, Reaction *> reaction = checkCollisionsAndReac(env, m, generator, sens); // On vérifie si une réaction est possible
		Molecule *molReac = reaction.first;
		Reaction *r = reaction.second;
		if(r) // S'il y a une réaction
		{
			nbReactions++;
			Molecule *p1 = new Molecule(r->getProduit1(), m->getX(), m->getY(), m->getZ()); // On crée la nouvelle molécule produite
			env->ajoutMolecule(p1); // On l'ajoute
			p1->getEspece()->pop++; // On met à jour la population
			p1->traitee = sens; // On la rend déjà traitée
			
			if(sens) // Le sens d'insertion dans la nouvelle liste change en fonction du sens de lecture
			{
				listeMoleculesMaj.push_back(p1); // On l'insère dans la nouvelle liste
				if(r->get2Produits()) // S'il y a 2 produits
				{
					Molecule *p2 = new Molecule(r->getProduit2(), m->getX(), m->getY(), m->getZ()); // On crée le deuxième produit
					p2->traitee = sens;
					listeMoleculesMaj.push_back(p2);
					env->ajoutMolecule(p2); // On le rajoute
					p2->getEspece()->pop++;
				}
			}
			else
			{
				listeMoleculesMaj.insert(listeMoleculesMaj.begin(), p1); // S'il y a 2 produits
				if(r->get2Produits())
				{
					Molecule *p2 = new Molecule(r->getProduit2(), m->getX(), m->getY(), m->getZ()); // On crée le deuxième produit
					p2->traitee = sens;
					listeMoleculesMaj.insert(listeMoleculesMaj.begin(), p2);
					env->ajoutMolecule(p2); // On le rajoute
					p2->getEspece()->pop++;
				}
			}

			env->removeMolecule(m); // On enlève le premier réactif
			m->getEspece()->pop--; // On met à jour la population
			m->traitee = sens;
			if(std::find(aSuppr.begin(), aSuppr.end(), m) == aSuppr.end()) // On vérifie si elle a déjà été rajoutée
			{
				aSuppr.push_back(m); // On la met dans la liste des molécules à supprimer
			}
			
			if(molReac) // S'il y a 2 réactifs
			{
				env->removeMolecule(molReac); // On enlève le second réactif
				molReac->getEspece()->pop--; // On met à jour la population
				molReac->traitee = sens;
				if(std::find(aSuppr.begin(), aSuppr.end(), molReac) == aSuppr.end()) // On vérifie si elle a déjà été rajoutée
				{
					aSuppr.push_back(molReac); // On la met dans la liste des molécules à supprimer
				}
			}
		}
		else // S'il n'y a pas de réaction
		{
			if(sens) // Le sens d'insertion dans la nouvelle liste change en fonction du sens de lecture
			{
				listeMoleculesMaj.push_back(m);
			}
			else
			{
				listeMoleculesMaj.insert(listeMoleculesMaj.begin(), m);
			}
			m->traitee = sens;
		}
	}

	listeMolecules = listeMoleculesMaj; // On écrase la nouvelle liste de molécule 
	
	
	for(EspeceMoleculaire *e : especes) // On met à jour le vecteur de résultats
    {
        results.push_back(e->pop);
    }

	for(Molecule *mol : aSuppr) // On supprime les molécules inutiles
	{
		delete mol;
	}

	results.push_back((double) nbReactions); // On met le nombre de réactions

	return results;
}

bool collision(Molecule *m1, Molecule *m2) // Vérifie si il y a une collision entre 2 molécules
{
	if(m1 && m2)
	{
		double sqDistance = pow(m2->getX() - m1->getX(), 2);
		sqDistance += pow(m2->getY() - m1->getY(), 2);
		sqDistance += pow(m2->getZ() - m1->getZ(), 2);
		double sqDistanceRequise = pow((m1->getEspece()->getTaille() + m2->getEspece()->getTaille()) / 2, 2);
		return sqDistance < sqDistanceRequise;		
	}
	return false;
}

Reaction* getReactionBi(Molecule *m1, Molecule *m2) // Renvoie une réaction bi-moléculaire impliquant m1 et m2
{
	if(m1 && m2)
	{
		for(auto&& r : reactions)
		{
			if (r->get2Reac()) { // Si c'est bi-moléculaire
			
				EspeceMoleculaire *r1 = r->getReac1();
				EspeceMoleculaire *r2 = r->getReac2();

				if((r1 == m1->getEspece() && r2 == m2->getEspece()) || (r1 == m2->getEspece() && r2 == m1->getEspece()))
				{
					return r;
				}
			}
		}
	}
	return NULL;	
}

Reaction* getReactionMono(Molecule *m) // Renvoie une réaction mono-moléculaire impliquant m
{
	if(m)
	{
		for(auto&& r : reactions)
		{
			if(!r->get2Reac() && r->getReac1() == m->getEspece())
			{
				return r;
			}
		}
	}
	return NULL;	
}

// Vérifie les collisions pour la molécule m et renvoie une réaction si une se produit avec la molécule associée s'il y en a une
std::pair<Molecule*, Reaction *> checkCollisionsAndReac(Environnement *env, Molecule *m, std::minstd_rand rng, bool sens)
{
	int mI, mJ, mK;
	std::tie(mI, mJ, mK) = env->coords2Indices(m->getX(), m->getY(), m->getZ()); // Indices I, J, K de l'environnement où se trouve m
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	for(int envI = mI - 1; envI <= mI + 1; envI++) // On regarde dans chaque cube autour du cube où est m
	{
		if(envI < 0 || envI >= env->cubeSize()) // Pour vérifier que l'on ne déborde pas du cube
		{
			continue;
		}
		for(int envJ = mJ - 1; envJ <= mJ + 1; envJ++)
		{
			if(envJ < 0 || envJ >= env->cubeSize()) // Pour vérifier que l'on ne déborde pas du cube
			{
				continue;
			}
			for(int envK = mK - 1; envK <= mK + 1; envK++)
			{
				if(envK < 0 || envK >= env->cubeSize()) // Pour vérifier que l'on ne déborde pas du cube
				{
					continue;
				}
				std::vector<Molecule*> &listMol = env->getListIndices(envI, envJ, envK); // On récupère la lite de molécules
				for(auto&& molVoisine : listMol)
				{
					if(collision(m, molVoisine)) // Si on tamponne une autre molécule
					{
						Reaction *rBi = getReactionBi(m, molVoisine); // On vérifie si il y a une réaction bi-moléculaire
						if(rBi && distribution(rng) < rBi->getProba() && molVoisine->traitee != sens) // Si une réaction bi-moléculaire se produit et que la seconde molécule n'est pas déjà traitée
						{
							return std::pair<Molecule*, Reaction *>(molVoisine, rBi);
						}
						else // Si ça ne réagit pas
						{
							m->unmove(env); //On remet la molécule à sa place initiale
							return std::pair<Molecule*, Reaction *>(NULL, checkReactionMono(m, rng)); // On vérifie si une réaction mono-moléculaire se produit
						}
					}
				}				
			}
		}
	}

	//Si la molécule n'a tamponné aucune molécule
	return std::pair<Molecule*, Reaction *>(NULL, checkReactionMono(m, rng));

}

Reaction* checkReactionMono(Molecule *m, std::minstd_rand rng) // Vérifie si une réaction mono-moléculaire se produit pour m et renvoie la réaction
{
	Reaction *rMono = getReactionMono(m); // On vérifie si il y a une réaction mono-moléculaire
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	if(rMono && distribution(rng) < rMono->getProba()) // Si une réaction Mono-moléculaire se produit
	{
		return rMono;
	}
	else
	{
		return NULL;
	}
}