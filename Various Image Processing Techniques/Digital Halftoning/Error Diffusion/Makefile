all: Problem2b

Problem2b: Problem2b.o ErrorDiffusion.o
	g++ Problem2b.o ErrorDiffusion.o -o Problem2b

Problem2b.o: Problem2b.cpp
	g++ -c Problem2b.cpp

ErrorDiffusion.o: ErrorDiffusion.cpp
	g++ -c ErrorDiffusion.cpp