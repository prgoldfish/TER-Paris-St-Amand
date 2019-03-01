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
/*%token INTEGER*/
%token NUMBER
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
LISTID	: IDENT {especes.push_back(new EspeceMoleculaire($1)); std::cout << "SPECIES IDENT" << std::endl;}
		| LISTID COMMA IDENT {especes.push_back(new EspeceMoleculaire($3)); std::cout << "SPECIES IDENT COMMA" << std::endl;}
;
SIZEM	: SIZE LP IDENT RP EQUALS NUMBER SEMI {
													for(EspeceMoleculaire* e : especes) 
													{
														std::cout << $3 << std::endl;
														if(e->getNom() == $3) 
														{
															e->setTaille(atoi($6));
															break;
														}
													}
													std::cout << "SIZE" << std::endl;
												}
;
SPEEDM	: SPEED LP IDENT RP EQUALS NUMBER SEMI {
													for(EspeceMoleculaire* e : especes) 
													{
														if(e->getNom() == $3) 
														{
															e->setVitesse(atof($6));
															break;
														}
													}
													std::cout << "SPEED" << std::endl;
												}
;
POPM	: POP LP IDENT RP EQUALS NUMBER SEMI {
													for(EspeceMoleculaire* e : especes) 
													{
														if(e->getNom() == $3) 
														{
															e->setPop(atoi($6));
															break;
														}
													}
													std::cout << "POP" << std::endl;
												}
;
DIA		: DIAM EQUALS NUMBER SEMI {diametre = atoi($3); std::cout << "DIAM" << std::endl;}
;
REACT	: IDENT REACTID ARROW IDENT REACTID LB NUMBER RB SEMI {
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
																std::cout << "REACT" << std::endl;
															 }
;
REACTID	: {	char txt[1] = "";
			$$ = txt;
			std::cout << "REACTIDENT" << std::endl;}
		| PLUS IDENT {$$ = $2; std::cout << "PLUS REACTIDENT" << std::endl;}
;
SDECL	: DECL
		| SDECL DECL
;
SINST	: INST
		| SINST INST
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