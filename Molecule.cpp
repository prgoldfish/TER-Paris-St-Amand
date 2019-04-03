#include "Molecule.h"


std::minstd_rand Molecule::generator(std::chrono::system_clock::now().time_since_epoch().count());

Molecule::Molecule(EspeceMoleculaire *e)
{
	std::uniform_real_distribution<double> distribution(0.0,1.0);
	double r = ((double) diametre) / 2;
	r *= distribution(generator);
	double theta = 2 * M_PI * distribution(generator);
	double phi = M_PI * distribution(generator);
	x = r * sin(phi) * cos(theta);
	y = r * sin(phi) * sin(theta);
	z = r * cos(phi);
}

void Molecule::move(double vitesse)
{
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    double theta = 2 * M_PI * distribution(generator);
	double phi = M_PI * distribution(generator);
    x += vitesse * sin(phi) * cos(theta);
	y += vitesse * sin(phi) * sin(theta);
	z += vitesse * cos(phi);
}

Environnement::Environnement()
{
    tailleCube = maxTaille();
    int nbCubes1D = ceil(tailleCube / (double) diametre);
    env3D = std::vector<std::vector<std::vector<std::vector<Molecule *>>>>();
    for(size_t i = 0; i < nbCubes1D; i++)
    {
        std::vector<std::vector<std::vector<Molecule *>>> env2D;
        env3D.push_back(env2D);
        for (size_t j = 0; j < nbCubes1D; j++)
        {
            std::vector<std::vector<Molecule *>> env1D;
            env2D.push_back(env1D);
            for(size_t k = 0; k < nbCubes1D; k++)
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
