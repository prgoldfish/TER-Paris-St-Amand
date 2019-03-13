CXX=g++
CFLAGS=-Wall -std=c++11
LDFLAGS=-ll
EXEC=analyLex


all: $(EXEC)

analyLex: parser.tab.o AnalyseurFlex.o main.o EspeceMoleculaire.o Reaction.o
					$(CXX) AnalyseurFlex.o parser.tab.o main.o EspeceMoleculaire.o Reaction.o -o analyLex $(LDFLAGS)

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

AnalyseurFlex.cpp: AnalyseurFlex.l
					flex -o AnalyseurFlex.cpp AnalyseurFlex.l

parser.tab.cpp: parser.y
					bison parser.y -d -o parser.tab.cpp

clean: 
					rm -rf *.o

cleanGen: 
					rm -rf AnalyseurFlex.cpp parser.tab.cpp

cleanAll: clean cleanGen

