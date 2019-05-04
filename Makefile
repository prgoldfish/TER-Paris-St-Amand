CXX=g++ -g
CFLAGS=-Wall -std=c++11 -I/usr/include/python2.7
LDFLAGS=-ll -lpython2.7
EXEC=analyLex


all: $(EXEC)

analyLex: parser.tab.o AnalyseurFlex.o main.o EspeceMoleculaire.o Reaction.o Simulation.o SortieCSV.o SortieGraph.o Molecule.o
					$(CXX) AnalyseurFlex.o parser.tab.o main.o EspeceMoleculaire.o Reaction.o Simulation.o SortieCSV.o SortieGraph.o Molecule.o -o analyLex $(LDFLAGS)

AnalyseurFlex.o : AnalyseurFlex.cpp
					$(CXX) -o AnalyseurFlex.o -c AnalyseurFlex.cpp $(CFLAGS)

parser.tab.o : parser.tab.cpp
					$(CXX) -o parser.tab.o -c parser.tab.cpp $(CFLAGS)

main.o : main.cpp
					$(CXX) -o main.o -c main.cpp $(CFLAGS)

EspeceMoleculaire.o : EspeceMoleculaire.cpp EspeceMoleculaire.h
					$(CXX) -o EspeceMoleculaire.o -c EspeceMoleculaire.cpp $(CFLAGS)

Reaction.o : Reaction.cpp Reaction.h
					$(CXX) -o Reaction.o -c Reaction.cpp $(CFLAGS)

Simulation.o : Simulation.cpp Simulation.h
					$(CXX) -o Simulation.o -c Simulation.cpp $(CFLAGS)

SortieCSV.o : SortieCSV.cpp SortieCSV.h
					$(CXX) -o SortieCSV.o -c SortieCSV.cpp $(CFLAGS)

SortieGraph.o : SortieGraph.cpp SortieGraph.h
					$(CXX) -o SortieGraph.o -c SortieGraph.cpp $(CFLAGS)

Molecule.o : Molecule.cpp Molecule.h
					$(CXX) -o Molecule.o -c Molecule.cpp $(CFLAGS)

AnalyseurFlex.cpp: AnalyseurFlex.l
					flex -o AnalyseurFlex.cpp AnalyseurFlex.l

parser.tab.cpp: parser.y
					bison parser.y -d -o parser.tab.cpp

clean: 
					rm -rf *.o

cleanGen: 
					rm -rf AnalyseurFlex.cpp parser.tab.cpp

cleanAll: clean cleanGen

