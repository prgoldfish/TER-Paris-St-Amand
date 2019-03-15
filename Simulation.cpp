#include "Simulation.h"


std::vector<double> simulationSimpleStep()
{
    std::vector<double> concentrations;
    std::minstd_rand generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(reactions.begin(), reactions.end(), generator);


    for(Reaction *r : reactions)
    {
        if(r->get2Reac()) //Bi-moléculaire
        {
            int nbChocs = getNbChocs(r->getReac1()->pop, r->getReac2()->pop, generator); 
        
        }
        else //Mono-moléculaire
        {
            
        }
        
    }
}


int getNbChocs(int nEm1, int nEm2, std::minstd_rand rng)
{
    double alpha = 7.4e-7;
    double volume = 4.0 * M_PI * 3.0 *  pow((double) diametre, 3.0);
    double nb = alpha * nEm1 * nEm2 / (volume * volume);
    int nbChocs = (int) nb;
    double decPart = nb - nbChocs;
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    if(distribution(rng) < decPart)
    {
        nbChocs++;
    }
    return nbChocs;




}