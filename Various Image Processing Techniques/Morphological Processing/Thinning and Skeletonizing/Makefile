all: Problem3b

Problem3b: Problem3b.o HitOrMiss.o
	g++ Problem3b.o HitOrMiss.o -o Problem3b

Problem3b.o: Problem3b.cpp
	g++ -c Problem3b.cpp

HitOrMiss.o: HitOrMiss.cpp HitOrMiss.h
	g++ -c HitOrMiss.cpp