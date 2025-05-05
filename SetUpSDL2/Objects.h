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
	int pipeX, pipe1Y, pipe2Y, pipeW, pipeH, pipeDistance, passHole, scoreMeter;
	static const int rows = 4, cols = 3;
	vector<vector<int>> pos_pipes;
	Pipe();
	void randomPositionGenerator();
};

#endif