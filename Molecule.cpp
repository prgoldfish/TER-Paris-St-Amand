#include "Molecule.h"
#include <iostream>


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

bool Molecule::move(Environnement *env)
{
    env->removeMolecule(this);
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
        env->ajoutMolecule(this);
        return false;
    }
    env->ajoutMolecule(this);
    return true;
}

void Molecule::unmove(Environnement *env)
{
    env->removeMolecule(this);
    x = lastX;
    y = lastY;
    z = lastZ;
    env->ajoutMolecule(this);
}

Environnement::Environnement()
{
    tailleCube = maxTaille();
    int nbCubes1D = ceil(diametre / (double) tailleCube);
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

std::vector<Molecule *>& Environnement::getListIndices(int i, int j, int k)
{
    return env3D[i][j][k];
}

std::vector<Molecule *>& Environnement::getListCoords(double x, double y, double z)
{
    //Translation des coordonées de la molécules en indices de la grille 3D
    std::tuple<int, int, int> ind = coords2Indices(x, y, z);
    int i = std::get<0>(ind);
    int j = std::get<1>(ind);
    int k = std::get<2>(ind);
    //std::cout << "i : " << i << "\tj : " << j << "\tk : " << k << std::endl;
    return env3D[i][j][k];
}

std::tuple<int, int, int> Environnement::coords2Indices(double x, double y, double z)
{
    int i = x + diametre / 2; //On met l'origine dans le même coin que celui de env3D
    int j = y + diametre / 2;
    int k = z + diametre / 2;
    i /= tailleCube;
    j /= tailleCube;
    k /= tailleCube;

    if(x < -51 || x > 51 || y < -51 || y > 51 || z < -51 || z > 51)
    {
        std::cout << "X coords2I : " << x << std::endl;
        std::cout << "Y coords2I : " << y << std::endl;
        std::cout << "Z coords2I : " << z << std::endl;
    }

    return std::tuple<int, int, int>(i, j, k);
}

void Environnement::ajoutMolecule(Molecule *m)
{
    double x = m->getX(), y = m->getY(), z = m->getZ();
    if(x < -51 || x > 51 || y < -51 || y > 51 || z < -51 || z > 51)
    {
        std::cout << "X ajoutMol : " << x << std::endl;
        std::cout << "Y ajoutMol : " << y << std::endl;
        std::cout << "Z ajoutMol : " << z << std::endl;
    }

    std::vector<Molecule *> &liste = getListCoords(m->getX(), m->getY(), m->getZ());
    liste.push_back(m);
    return;
}

std::vector<Molecule *>& Environnement::findMolecule(Molecule *m)
{
    return  getListCoords(m->getX(), m->getY(), m->getZ());
}

void Environnement::removeMolecule(Molecule *m)
{
    std::vector<Molecule *> &list = findMolecule(m);
    auto it = std::find(list.begin(), list.end(), m);
    if(it == list.end())
    {
        std::tuple<int, int, int> ind = coords2Indices(m->getX(), m->getY(), m->getZ());
        int i = std::get<0>(ind);
        int j = std::get<1>(ind);
        int k = std::get<2>(ind);
        std::cout << "IMPOSSIBILITE D'EFFACER UNE MOLECULE !!!" << std::endl;
        std::cout << "Espece : " << m->getEspece()->getNom() << std::endl;
        std::cout << "X : " << m->getX() << std::endl;
        std::cout << "Y : " << m->getY() << std::endl;
        std::cout << "Z : " << m->getZ() << std::endl;
        std::cout << "R : " << m->getR() << std::endl;
        std::cout << "I : " << i << std::endl;
        std::cout << "J : " << j << std::endl;
        std::cout << "K : " << k << std::endl;
        rechercheTotale(m, this);
        exit(-1);
    }
    else
    {
        list.erase(it);
        //std::cout << "EFFACE !!!" << std::endl;
    }
}

void rechercheTotale(Molecule *m, Environnement *env)
{
    for(int i = 0; i < env->cubeSize(); i++)
    {
        for(int j = 0; j < env->cubeSize(); j++)
        {
            for(int k = 0; k < env->cubeSize(); k++)
            {
                std::vector<Molecule *> &list = env->getListIndices(i, j, k);
                auto it = std::find(list.begin(), list.end(), m);
                if(it != list.end())
                {
                    std::cout << "Molecule trouvee dans la recherche totale !!!" << std::endl;
                    std::cout << "I : " << i << std::endl;
                    std::cout << "J : " << j << std::endl;
                    std::cout << "K : " << k << std::endl;
                    return;
                }
            }
        }
    }
    std::cout << "Molecule NON trouvee dans la recherche totale !!!" << std::endl;
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