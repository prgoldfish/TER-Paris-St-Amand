%{
	#include <cstdlib>
	#include "y.tab.h"
%}

DIGITS [0-9]
ALPHA [a-zA-Z]
ALPHANUM [a-zA-Z][a-zA-Z0-9]

%%

{DIGITS}+			yylval = atoi(yytext); return INTEGER;

{ALPHANUM}+			yylval = yytext; return IDENT;

{DIGIT}+"."{DIGIT}*	yylval = atof(yytext); return FLOAT;

"+"					return PLUS;



