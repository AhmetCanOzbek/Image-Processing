all: Problem2c

Problem2c: Problem2c.o ErrorDiffusion.o
	g++ Problem2c.o ErrorDiffusion.o -o Problem2c

Problem2c.o: Problem2c.cpp
	g++ -c Problem2c.cpp

ErrorDiffusion.o: ErrorDiffusion.cpp
	g++ -c ErrorDiffusion.cpp