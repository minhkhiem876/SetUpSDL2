#ifndef OBJECTS_H
#define OBJECTS_H
#include <iostream>
#include <SDL.h>
#include "Resource.h"
#include <SDL_image.h>
#include <vector>
using namespace std;


struct Bird {
	const float MAX_ANGLE = 90.0f;
	const float MIN_ANGLE = 25.0f;
	const float ANGLE_FALL_SPEED = 2.0f;
	const int MAX_DROP_SPEED = 10;

	int birdPosX, birdPosY, vel, score, widthBird, heightBird;
	float birdAngle;
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

struct AnimationBird {
	static const int BIRD_FLY_FRAME_COUNT = 8;
	static const int BIRD_DEAD_FRAME_COUNT = 12;
	static const int FRAME_DELAY = 100;
	static const int FRAME_DEAD_DELAY = 30;
	
	SDL_Texture* birdFrames[BIRD_FLY_FRAME_COUNT];
	SDL_Texture* birdDeadFrames[BIRD_DEAD_FRAME_COUNT];

	int currentFrame;;
	Uint32 lastFrameTime;

	int currentDeadFrame;
	Uint32 lastDeadFrameTime;
	
	AnimationBird();
	void loadFrame(SDL_Renderer* renderer);
	void updateDeadAnimation(Bird& bird);
	void updateBirdAnimation();
	void reset();
};
#endif