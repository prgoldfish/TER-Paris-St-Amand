#include "Molecule.h"


std::minstd_rand Molecule::generator(std::chrono::system_clock::now().time_since_epoch().count());

Molecule::Molecule(EspeceMoleculaire *e)
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

Molecule::Molecule(EspeceMoleculaire *e, double coordX, double coordY, double coordZ)
{
    espece = e;
	x = coordX;
	y = coordY;
	z = coordZ;
}

void Molecule::move()
{
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    double theta = 2 * M_PI * distribution(generator);
	double phi = M_PI * distribution(generator);
    lastX = x;
    lastY = y;
    lastZ = z;
    x += espece->getVitesse() * sin(phi) * cos(theta);
	y += espece->getVitesse() * sin(phi) * sin(theta);
	z += espece->getVitesse() * cos(phi);
}

void Molecule::unmove()
{
    x = lastX;
    y = lastY;
    z = lastZ;
}

Environnement::Environnement()
{
    tailleCube = maxTaille();
    int nbCubes1D = ceil(tailleCube / (double) diametre);
    env3D = std::vector<std::vector<std::vector<std::vector<Molecule *>>>>();
    for(int i = 0; i < nbCubes1D; i++)
    {
        std::vector<std::vector<std::vector<Molecule *>>> env2D;
        env3D.push_back(env2D);
        for (int j = 0; j < nbCubes1D; j++)
        {
            std::vector<std::vector<Molecule *>> env1D;
            env2D.push_back(env1D);
            for(int k = 0; k < nbCubes1D; k++)
            {
                std::vector<Molecule *> listMolecules;
                env1D.push_back(listMolecules);
            }
            
        }
    }    
}

std::vector<Molecule *> Environnement::getListIndices(int i, int j, int k)
{
    return env3D[i][j][k];
}

std::vector<Molecule *> Environnement::getListCoords(double x, double y, double z)
{
    //Translation des coordonées de la molécules en indices de la grille 3D
    int i = x + diametre / 2; //On met l'origine dans le même coin que celui de env3D
    int j = x + diametre / 2;
    int k = x + diametre / 2;
    i /= tailleCube;
    j /= tailleCube;
    k /= tailleCube;

    return env3D[i][j][k];
}


void Environnement::ajoutMolecule(Molecule *m)
{
    getListCoords(m->getX(), m->getY(), m->getZ()).push_back(m);
}

std::vector<Molecule *> Environnement::findMolecule(Molecule *m)
{
    return  getListCoords(m->getX(), m->getY(), m->getZ());
}

int maxTaille()
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