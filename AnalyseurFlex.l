%option bison-bridge
%option noyywrap

%{
	#define YYSTYPE char*
	#include "parser.tab.hpp"
%}


DIGITS 				[0-9]
ALPHA 				[a-zA-Z]
ALPHANUM 			[a-zA-Z][a-zA-Z0-9]

%%


"diametre"				return yy::parser::token::DIAM;

"size"					return yy::parser::token::SIZE;

{DIGITS}+				*yylval = yytext; return yy::parser::token::INTEGER;

{ALPHANUM}+				*yylval = yytext; return yy::parser::token::IDENT;

{DIGITS}+"."{DIGITS}*	*yylval = yytext; return yy::parser::token::FLOAT;

"+"						return yy::parser::token::PLUS;

"species"				return yy::parser::token::SPECIES;

"("						return yy::parser::token::LP;

")"						return yy::parser::token::RP;

","						return yy::parser::token::COMMA;

"//".*					{}

";"						return yy::parser::token::COMMA;

"="						return yy::parser::token::EQUALS;

"speed"					return yy::parser::token::SPEED;

"pop"					return yy::parser::token::POP;

"=>"					return yy::parser::token::ARROW;

"["						return yy::parser::token::LB;

"]"						return yy::parser::token::RB;

%%

