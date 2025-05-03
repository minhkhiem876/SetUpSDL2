#include "Logic.h"
#include "Resource.h"

void updateBird(Bird& bird) {
	if (bird.fly) {
		bird.birdPosY -= 10; // fly
		bird.flyUp++;
		if (bird.flyUp >= 5) {
			bird.fly = false;
			bird.flyUp = 0;
			bird.timeAccel = 0;
		}
	}
	else {
		bird.timeAccel++;
		bird.birdPosY += bird.timeAccel / 2; // drop follow accel;
	}
}

bool checkCollision(const Bird& bird, const Pipe& pipes) {
	int birdW = 34, birdH = 24;
	int pipeW = pipes.pipeW;
	int pipeH = pipes.pipeH;

	SDL_Rect birdRect = { bird.birdPosX, bird.birdPosY, birdW, birdH };
	SDL_Rect upperPipe = { pipes.pipeX, pipes.pipe2Y, pipeW, pipeH };
	SDL_Rect lowerPipe = { pipes.pipeX, pipes.pipe1Y, pipeW, pipeH };

	bool hitTop = SDL_HasIntersection(&birdRect, &upperPipe);
	bool hitBottom = SDL_HasIntersection(&birdRect, &lowerPipe);
	bool outOfBounds = bird.birdPosY < 0 || bird.birdPosY + birdH > SCREEN_HEIGHT;

	return hitTop || hitBottom || outOfBounds;
}

void updatePipes(Pipe& pipes, Bird& bird) {
	pipes.pipeX -= pipeSpeed; 

	if (pipes.pipeX + pipes.pipeW < 0) {
		pipes.pipeX = SCREEN_WIDTH;
		pipes.randomPositionGenerator();
		pipes.hasPassed = false;
	}

	else if (pipes.pipeX + pipes.pipeW < bird.birdPosX && !pipes.hasPassed) {
		bird.score++;
		pipees.hasPassed = true;
	}
}