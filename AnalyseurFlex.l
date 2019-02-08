%{
	#include <cstdlib>
	#include "y.tab.h"
%}

DIGITS 				[0-9]
ALPHA 				[a-zA-Z]
ALPHANUM 			[a-zA-Z][a-zA-Z0-9]

%%

{DIGITS}+			yylval = atoi(yytext); return INTEGER;

{ALPHANUM}+			yylval = yytext; return IDENT;

{DIGITS}+"."{DIGITS}*	yylval = atof(yytext); return FLOAT;

"+"					return PLUS;

"species"			return SPECIES;

"("					return LP;

")"					return RP;

","					return COMMA;

"//".*				{}

";"					return COMMA;

"="					return EQUALS;

"size"				return SIZE;

"speed"				return SPEED;

"pop"				return POP;

"diametre"			return DIAM;

"=>"				return ARROW;

"["					return LB;

"]"					return RB;

%%

