#ifndef ESPECEMOLECULAIRE_H
#define ESPECEMOLECULAIRE_H

#include <string>

class EspeceMoleculaire
{
private:
    std::string nom; // Nom de l'espèce
    int taille; // Taille en nm
    float vitesse; // Vitesse
public:
    int pop; // Nombre de molécules de cette espèce

    EspeceMoleculaire();
    EspeceMoleculaire(std::string nom);
    EspeceMoleculaire(std::string nom, int taille, float vitesse, int pop);
    ~EspeceMoleculaire();

    std::string getNom();
    void setTaille(int);
    void setVitesse(float);
    float getVitesse();
    int getTaille();
};

#endif
