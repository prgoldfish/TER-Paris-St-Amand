#ifndef ESPECEMOLECULAIRE_H
#define ESPECEMOLECULAIRE_H

#include <string>

class EspeceMoleculaire
{
private:
    std::string nom;
    int taille;
    float vitesse;
public:
    int pop;

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
