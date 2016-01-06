all: Problem3a

Problem3a: Problem3a.o HitOrMiss.o
	g++ Problem3a.o HitOrMiss.o -o Problem3a

Problem3a.o: Problem3a.cpp
	g++ -c Problem3a.cpp

HitOrMiss.o: HitOrMiss.cpp HitOrMiss.h
	g++ -c HitOrMiss.cpp