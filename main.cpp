#include <cstdlib>
#include "parser.tab.hpp"
#include "EspeceMoleculaire.h"
#include "Reaction.h"

int diametre;
std::vector<EspeceMoleculaire*> especes;
std::vector<Reaction*> reactions;

int main (int argc, char** argv)
{
    yy::parser parser;
    parser.parse();
    return 0;
}