#ifndef OBJECTS_H
#define OBJECTS_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
using namespace std;

struct Bird {
	int birdPosX, birdPosY, flyUp, timeAccel, score, widthBird, heightBird;
	bool fly;
	Bird();
};

struct Pipe {
	static const int rows = 4, cols = 3;
	int pipeX, pipe1Y, pipe2Y, pipeW, pipeH, pipeDistance, passHole, scoreMeter;
	vector<vector<int>> pos_pipes;
	// col 1 is posx, col 2 is pos1y, col 3 is pos2y
	Pipe();
	void randomPositionGenerator();
};

#endif