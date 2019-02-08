%{
	#include "parser.tab.h"
%}

DIGITS 				[0-9]
ALPHA 				[a-zA-Z]
ALPHANUM 			[a-zA-Z][a-zA-Z0-9]

%%


"diametre"			return DIAM;

"size"				return SIZE;

{DIGITS}+			yylval = yytext; return INTEGER;

{ALPHANUM}+			yylval = yytext; return IDENT;

{DIGITS}+"."{DIGITS}*	yylval = yytext; return FLOAT;

"+"					return PLUS;

"species"			return SPECIES;

"("					return LP;

")"					return RP;

","					return COMMA;

"//".*				{}

";"					return COMMA;

"="					return EQUALS;

"speed"				return SPEED;

"pop"				return POP;

"=>"				return ARROW;

"["					return LB;

"]"					return RB;

%%

