#include "Objects.h"
#include "Resource.h"
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

Bird::Bird() {
	birdAngle = 0.0f;
	widthBird = 0;
	heightBird = 0;
	birdPosX = SCREEN_WIDTH / 5;
	birdPosY = SCREEN_HEIGHT / 3; 
	vel = 0;
	score = 0;
}

Pipe::Pipe() {
	pipeX = SCREEN_WIDTH;
	pipe1Y = 0;
	pipe2Y = 0;
	pipeW = 0;
	pipeH = 0;
	pipeDistance = PIPE_DISTANCE;
	scoreMeter = 0;
	passHole = 150;
	pos_pipes = vector<vector<int>>(rows, vector<int>(cols));
}

void Pipe::randomPositionGenerator() {
	pipe1Y = (rand() % (SCREEN_HEIGHT - passHole + 1)) + passHole;
	pipe2Y = pipe1Y - passHole - pipeH;
}

AnimationBird :: AnimationBird() {
	currentFrame = 0;
	lastFrameTime = 0;
}

void AnimationBird::loadFrame (SDL_Renderer* renderer){
	for (int i = 0; i < BIRD_FLY_FRAME_COUNT; i++) {
		string path = "C:/Users/khiem/Desktop/SetUpSDL2/SetUpSDL2/animationBird/Bird_" + to_string(i) + ".png";
		birdFrames[i] = IMG_LoadTexture(renderer, path.c_str());
		if (!birdFrames[i]) {
			SDL_Log("Failed to lead bird frame: %s", SDL_GetError());
			return;
		}
	}
}

void AnimationBird :: updateBirdAnimation() {
	Uint32 currentTime = SDL_GetTicks();
	if (currentTime > lastFrameTime + FRAME_DELAY) {
		currentFrame = (currentFrame + 1) % BIRD_FLY_FRAME_COUNT;
		lastFrameTime = currentTime;
	}
}









