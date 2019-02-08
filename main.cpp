#include <cstdlib>
#include "parser.tab.h"


int main (int argc, char** argv)
{
    yyparse();
    return 0;
}