#include "Objects.h"
#include <cstdlib>

Bird::Bird() {
	birdPosX = SCREEN_WIDTH / 5;
	birdPosY = SCREEN_HEIGHT / 3; 
	flyUp = 0;
	timeAccel = 0;
	score = 0;
	fly = false;
}

Pipe::Pipe() {
	pipeX = SCREEN_WIDTH;
	pipe1Y = 0;
	pipe2Y = 0;
	pipeW = 0;
	pipeH = 0;
	pipeDistance = 250;
	bool hasPassed = false;
	passHole = 150;
	vector<vector<int>> pos_pipes(rows, vector<int>(cols));
}

void Pipe::randomPositionGenerator() {
	pipe1Y = (rand() % (SCREEN_HEIGHT - passHole + 1) + passHole;
	pipe2Y = pipe1Y - passHole - pipeH;
}







