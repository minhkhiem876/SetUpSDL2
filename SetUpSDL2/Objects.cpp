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
	passHole = PASS_HOLE;
	pos_pipes = vector<vector<int>>(rows, vector<int>(cols));
}

void Pipe::randomPositionGenerator() {
	pipe1Y = (rand() % (SCREEN_HEIGHT - passHole + 1)) + passHole;
	pipe2Y = pipe1Y - passHole - pipeH;
}

AnimationBird :: AnimationBird() {
	currentFrame = 0;
	lastFrameTime = 0;

	currentDeadFrame = 0;
	lastDeadFrameTime = 0; 
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
	for (int i = 0; i < BIRD_DEAD_FRAME_COUNT; i++) {
		string path = "C:/Users/khiem/Desktop/SetUpSDL2/SetUpSDL2/animationDead/Dead_" + to_string(i) + ".png";
		birdDeadFrames[i] = IMG_LoadTexture(renderer, path.c_str());
		if (!birdDeadFrames[i]) {
			SDL_Log("Failed to lead bird frame: %s", SDL_GetError());
			return;
		}
	}
}

void AnimationBird :: updateBirdAnimation() {
	Uint32 currentFrameTime = SDL_GetTicks();
	if (currentFrameTime > lastFrameTime + FRAME_DELAY) {
		currentFrame = (currentFrame + 1) % BIRD_FLY_FRAME_COUNT;
		lastFrameTime = currentFrameTime;
	}
}

void AnimationBird::updateDeadAnimation(Bird& bird) {
	Uint32 currentDeadFrameTime = SDL_GetTicks();
	if (currentDeadFrameTime > lastDeadFrameTime + FRAME_DEAD_DELAY && currentDeadFrame < BIRD_DEAD_FRAME_COUNT - 1) {
		currentDeadFrame = currentDeadFrame++;
		lastDeadFrameTime = currentDeadFrameTime;
		bird.birdPosY += 10;
	}
}

void AnimationBird::reset() {
	currentDeadFrame = 0;
	lastDeadFrameTime = 0;
}









