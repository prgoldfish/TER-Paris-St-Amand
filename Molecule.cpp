#include "Molecule.h"
#include <iostream>


std::minstd_rand Molecule::generator(std::chrono::system_clock::now().time_since_epoch().count()); // Moteur de nombre aléatoire

Molecule::Molecule(EspeceMoleculaire *e) // Construit une molécule avec des coordonées sphériques aléatoires converties en coordonnées cartésiennes afin d'être sur que la molécule soit dans l'environnement
{
    espece = e;
	std::uniform_real_distribution<double> distribution(0.0,1.0);
	double r = ((double) diametre) / 2;
	r *= distribution(generator);
	double theta = 2 * M_PI * distribution(generator);
	double phi = M_PI * distribution(generator);
	x = r * sin(phi) * cos(theta);
	y = r * sin(phi) * sin(theta);
	z = r * cos(phi);
}

Molecule::Molecule(EspeceMoleculaire *e, double coordX, double coordY, double coordZ) // Construit une molécule aux coordonnées x, y, z
{
    espece = e;
	x = coordX;
	y = coordY;
	z = coordZ;
}

bool Molecule::move(Environnement *env) // Tente de faire bouger la molécule dans une direction aléatoire et met à jour sa positio dans l'environnement. Renvoie true si le déplacement s'est effectué
{
    env->removeMolecule(this); // On enlève la molécule avant
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    double theta = 2 * M_PI * distribution(generator);
	double phi = M_PI * distribution(generator);
    lastX = x;
    lastY = y;
    lastZ = z;
    x += espece->getVitesse() * sin(phi) * cos(theta);
	y += espece->getVitesse() * sin(phi) * sin(theta);
	z += espece->getVitesse() * cos(phi);
    if(getR() > (diametre / 2))
    {
        x = lastX;
        y = lastY;
        z = lastZ;
        env->ajoutMolecule(this); // On la remet où elle était
        return false;
    }
    env->ajoutMolecule(this); // On la remet à ses nouvelles coordonnées
    return true;
}

void Molecule::unmove(Environnement *env) // Anule le déplacement d'une molécule et met à jour sa position dans l'environnement
{
    env->removeMolecule(this);
    x = lastX;
    y = lastY;
    z = lastZ;
    env->ajoutMolecule(this);
}

Environnement::Environnement() // Constructeur de l'environnement. C'est une grille 3D ou chaque cube contient la liste des molécules présentes dans le cube
{
    tailleCube = maxTaille(); // Taille d'un cube en nm. C'est la taille de la plus grosse molécule
    int nbCubes1D = ceil(diametre / (double) tailleCube); // Nombre de cubes par dimension
    for(int i = 0; i < nbCubes1D; i++)
    {
        std::vector<std::vector<std::vector<Molecule *>>> env2D;
        
        for (int j = 0; j < nbCubes1D; j++)
        {
            std::vector<std::vector<Molecule *>> env1D;
            for(int k = 0; k < nbCubes1D; k++)
            {
                std::vector<Molecule *> listMolecules;
                env1D.push_back(listMolecules);
            }
            env2D.push_back(env1D);
        }
        env3D.push_back(env2D);
    }    
}

std::vector<Molecule *>& Environnement::getListIndices(int i, int j, int k) // Renvoie une référence vers la liste des molécules aux indices i, j et k de l'environnement
{
    return env3D[i][j][k];
}

std::vector<Molecule *>& Environnement::getListCoords(double x, double y, double z) // Convertit les coordonées en indices et renvoie une référence vers la liste des molécules à ces indices dans l'environnement
{
    //Translation des coordonées de la molécules en indices de la grille 3D
    std::tuple<int, int, int> ind = coords2Indices(x, y, z);
    int i = std::get<0>(ind);
    int j = std::get<1>(ind);
    int k = std::get<2>(ind);
    return env3D[i][j][k];
}

std::tuple<int, int, int> Environnement::coords2Indices(double x, double y, double z) // Convertit les coordonées en indices
{
    int i = x + diametre / 2; //On met l'origine dans le même coin que celui de env3D
    int j = y + diametre / 2;
    int k = z + diametre / 2;
    i /= tailleCube;
    j /= tailleCube;
    k /= tailleCube;

    return std::tuple<int, int, int>(i, j, k);
}

void Environnement::ajoutMolecule(Molecule *m) // Ajoute une molécule dans l'environnement
{
    std::vector<Molecule *> &liste = getListCoords(m->getX(), m->getY(), m->getZ());
    liste.push_back(m);
}

std::vector<Molecule *>& Environnement::findMolecule(Molecule *m) // Renvoie la liste de molécule où m se trouve
{
    return  getListCoords(m->getX(), m->getY(), m->getZ());
}

void Environnement::removeMolecule(Molecule *m) // Cherche la molécule et la supprime de l'environnement
{
    std::vector<Molecule *> &list = findMolecule(m);
    auto it = std::find(list.begin(), list.end(), m);
    if(it != list.end()) // Si on trouve la molécule
    {
        list.erase(it);
    }
}

int maxTaille() // Renvoie la taille de la plus grosse molecule
{
    int max = 0;
    for(auto&& e : especes)
    {
        if(e->getTaille() > max)
        {
            max = e->getTaille();
        }
    }
    return max;
}