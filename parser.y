%{
	#include <iostream>
	#include <cstdlib>
	#include <string>
	#include "EspeceMoleculaire.h"
	int yyparse();
	int yylex();
	int yyerror(std::string s);
%}

%union {
	int intVal;
	float floatVal;
	char* textVal;
}
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
LISTID	: IDENT {}
		| IDENT COMMA LISTID
;
SIZEM	: SIZE LP IDENT RP EQUALS INTEGER SEMI
;
POPM	: POP LP IDENT RP EQUALS INTEGER SEMI
;
SPEEDM	: SPEED LP IDENT RP EQUALS FLOAT SEMI
;
DIA		: DIAM EQUALS INTEGER
;
REACT	: REACTID ARROW REACTID LB FLOAT RB SEMI
;
REACTID	: IDENT
		| IDENT PLUS IDENT
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