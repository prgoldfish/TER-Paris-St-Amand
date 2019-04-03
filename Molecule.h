#include <random>
#include <chrono>
#include <vector>

#include "EspeceMoleculaire.h"


extern int diametre;
extern std::vector<EspeceMoleculaire*> especes;

int maxTaille();

class Molecule
{
    private:
        double x, y, z;
        double lastX, lastY, lastZ;
        EspeceMoleculaire *espece;
        static std::minstd_rand generator;

    public:
        bool traitee;
        Molecule(EspeceMoleculaire *e);
        Molecule(EspeceMoleculaire *e, double x, double y, double z);
        ~Molecule(){}
        double getX(){return x;}
        double getY(){return y;}
        double getZ(){return z;}
        void move();
        void unmove();

};

class Environnement
{
    private: 
        std::vector<std::vector<std::vector<std::vector<Molecule *>>>> env3D;
        int tailleCube;

    public:
        Environnement();
        ~Environnement(){}
        std::vector<Molecule *> getListCoords(double x, double y, double z);
        std::vector<Molecule *> getListIndices(int i, int j, int k);
        std::vector<std::vector<std::vector<Molecule *>>>& operator[](size_t i){ return env3D[i];}
        void ajoutMolecule(Molecule *m);
        std::vector<Molecule *> findMolecule(Molecule *m);
        void removeMolecule(Molecule *m);
};