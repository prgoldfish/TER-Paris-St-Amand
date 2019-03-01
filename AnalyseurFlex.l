%option bison-bridge
%option noyywrap

%{
	 //{DIGITS}+				std::cout << "FLEXDIGITS" << std::endl; *yylval = yytext; return yy::parser::token::INTEGER;
	#define YYSTYPE char*
	#include "parser.tab.hpp"
%}


DIGITS 				[0-9]
ALPHANUM 			[a-zA-Z][a-zA-Z0-9]*

%%


"diametre"				std::cout << "FLEXDIAM" << std::endl; return yy::parser::token::DIAM;

"size"					std::cout << "FLEXSIZE" << std::endl; return yy::parser::token::SIZE;

"species"				std::cout << "FLEXSPECIES" << std::endl; return yy::parser::token::SPECIES;

"speed"					std::cout << "FLEXSPEED" << std::endl; return yy::parser::token::SPEED;

"pop"					std::cout << "FLEXPOP" << std::endl; return yy::parser::token::POP;

{ALPHANUM}+				std::cout << "FLEXALPHANUM" << std::endl; *yylval = yytext; return yy::parser::token::IDENT;

{DIGITS}+"."*{DIGITS}*	std::cout << "FLEXDIGITS" << std::endl; *yylval = yytext; return yy::parser::token::NUMBER;

"+"						std::cout << "FLEXPLUS" << std::endl; return yy::parser::token::PLUS;

"("						std::cout << "FLEXLP" << std::endl; return yy::parser::token::LP;

")"						std::cout << "FLEXRP" << std::endl; return yy::parser::token::RP;

","						std::cout << "FLEXCOMMA" << std::endl; return yy::parser::token::COMMA;

"//".*					{std::cout << "FLEXCOMMENT" << std::endl; }

[ \n\t\r]+				{std::cout << "FLEXWHITESPACE" << std::endl; }		

";"						std::cout << "FLEXSEMI" << std::endl; return yy::parser::token::SEMI;

"="						std::cout << "FLEXEQUALS" << std::endl; return yy::parser::token::EQUALS;

"->"					std::cout << "FLEXARROW" << std::endl; return yy::parser::token::ARROW;

"["						std::cout << "FLEXLB" << std::endl; return yy::parser::token::LB;

"]"						std::cout << "FLEXRB" << std::endl; return yy::parser::token::RB;

%%

