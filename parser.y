%{
	#include <iostream>
	#include <cstdlib>
	#include <string>
	#include "EspeceMoleculaire.h"
	#include "Reaction.h"
	int yyparse();
	int yylex();
	int yyerror(std::string s);

	extern std::vector<EspeceMoleculaire> especes;
%}


%token IDENT
%token INTEGER
%token FLOAT
%token SPECIES
%token LP
%token RP
%token LB
%token RB
%token COMMA
%token SEMI
%token EQUALS
%token SIZE
%token SPEED
%token POP
%token DIAM
%token PLUS
%token ARROW

%%
DECL : SPECIES LISTID SEMI
LISTID	: IDENT {especes.push_back(new EspeceMoleculaire(§1))}
		| IDENT COMMA LISTID {especes.push_back(new EspeceMoleculaire(§1))}
;
SIZEM	: SIZE LP IDENT RP EQUALS INTEGER SEMI
;
POPM	: POP LP IDENT RP EQUALS INTEGER SEMI
;
SPEEDM	: SPEED LP IDENT RP EQUALS FLOAT SEMI
;
DIA		: DIAM EQUALS INTEGER
;
REACT	: IDENT REACTID ARROW IDENT REACTID LB FLOAT RB SEMI
;
REACTID	: 
		| PLUS IDENT
;
SDECL	: DECL
		| DECL SDECL
;
SINST	: INST
		| INST SINST
;
INST	: REACT
		| DIA
		| SIZEM
		| SPEEDM
		| POPM
;
%%

int yyerror(std::string s) {
	std::cout << "yyerror : " << s << std::endl;
	return 0;
}