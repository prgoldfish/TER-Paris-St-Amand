%option bison-bridge
%option noyywrap

%{
	#define YYSTYPE char*
	#include <string>
	#include "parser.tab.hpp"
%}


DIGITS 				[0-9]

%%


"diametre"				return yy::parser::token::DIAM;

"size"					return yy::parser::token::SIZE;

"species"				return yy::parser::token::SPECIES;

"speed"					return yy::parser::token::SPEED;

"pop"					return yy::parser::token::POP;

[a-zA-Z][a-zA-Z0-9]*	*yylval = strdup(yytext); return yy::parser::token::IDENT;

{DIGITS}+"."*{DIGITS}*	*yylval = strdup(yytext); return yy::parser::token::NUMBER;

"+"						return yy::parser::token::PLUS;

"("						return yy::parser::token::LP;

")"						return yy::parser::token::RP;

","						return yy::parser::token::COMMA;

"//".*					{ }

[ \n\t\r]+				{ }		

";"						return yy::parser::token::SEMI;

"="						return yy::parser::token::EQUALS;

"->"					return yy::parser::token::ARROW;

"["						return yy::parser::token::LB;

"]"						return yy::parser::token::RB;

%%

