%{
	#include <iostream>
	#include <cstdlib>
	#include <string>
	#include <vector>
	#include "EspeceMoleculaire.h"
	#include "Reaction.h"
	int yyparse();
	int yylex(char**);
	int yyerror(std::string s);

	extern int diametre;
	extern std::vector<EspeceMoleculaire*> especes;
	extern std::vector<Reaction*> reactions;
%}

%language "c++"
%define api.value.type {char*}

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
MODELE	: SDECL SINST
;
DECL : SPECIES LISTID SEMI {std::cout << "SPECIES" << std::endl;}
;
LISTID	: IDENT {especes.push_back(new EspeceMoleculaire($1));}
		| IDENT COMMA LISTID {especes.push_back(new EspeceMoleculaire($1));}
;
SIZEM	: SIZE LP IDENT RP EQUALS INTEGER SEMI {
													for(EspeceMoleculaire* e : especes) 
													{
														if(e->getNom() == $3) 
														{
															e->setTaille(atoi($6));
															break;
														}
													}
												}
;
SPEEDM	: SPEED LP IDENT RP EQUALS FLOAT SEMI {
													for(EspeceMoleculaire* e : especes) 
													{
														if(e->getNom() == $3) 
														{
															e->setVitesse(atof($6));
															break;
														}
													}
												}
;
POPM	: POP LP IDENT RP EQUALS INTEGER SEMI {
													for(EspeceMoleculaire* e : especes) 
													{
														if(e->getNom() == $3) 
														{
															e->setPop(atoi($6));
															break;
														}
													}
												}
;
DIA		: DIAM EQUALS INTEGER SEMI {diametre = atoi($3);}
;
REACT	: IDENT REACTID ARROW IDENT REACTID LB FLOAT RB SEMI {
																EspeceMoleculaire *r1, *r2, *p1, *p2;
																bool dr = false;
																for(EspeceMoleculaire* e : especes)
																{
																	if(e->getNom() == $1){
																		r1 = e;
																		dr = true;
																	} 
																}
																dr = false;
																for(EspeceMoleculaire* e : especes) 
																{
																	if(e->getNom() == $2){
																		r2 = e;
																		dr = true;
																	}
																}
																bool dp = false;
																for(EspeceMoleculaire* e : especes)
																{
																	if(e->getNom() == $4){
																		p1 = e;
																		dp = true;
																	}
																}
																dp = false;
																for(EspeceMoleculaire* e : especes) 
																{
																	if(e->getNom() == $5){
																		p2 = e;
																		dp = true;
																	}
																}
																reactions.push_back(new Reaction(r1, r2, p1, p2, dr, dp, atof($7)));
															 }
;
REACTID	: {	char txt[1] = "";
			$$ = txt;}
		| PLUS IDENT {$$ = $2;}
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

void yy::parser::error(const std::string& msg) {
	std::cerr << "yyerror : " << msg << std::endl;
}