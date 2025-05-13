#include "Logic.h"
#include <iostream>
#include <SDL.h>
#include <vector>
#include "Resource.h"
using namespace std;

void birdFly(const Uint8* currentKeyStated, Bird& bird) {
	if (currentKeyStated[SDL_SCANCODE_SPACE]) {
		bird.vel = - FALL_SPEED;
		bird.birdAngle = bird.MIN_ANGLE;
	}

	bird.vel += 1;
	if (bird.vel > bird.MAX_DROP_SPEED) {
		bird.vel = bird.MAX_DROP_SPEED;
	}
	bird.birdPosY += bird.vel;

	if (bird.vel >= 0) {
		bird.birdAngle += bird.ANGLE_FALL_SPEED;
		if (bird.birdAngle > bird.MAX_ANGLE) {
			bird.birdAngle = bird.MAX_ANGLE;
		}
	}
	else {
		bird.birdAngle = bird.MIN_ANGLE;
	}
}

void pipeRunning(Pipe& pipes, Graphics& graphics, SDL_Texture* pipe, const int pipeSpeed, bool gen) {
	for (int i = 0; i < 4; i++) {
		pipes.pos_pipes[i][0] -= pipeSpeed;
		graphics.advancedRenderTexture(pipe, pipes.pos_pipes[i][0], pipes.pos_pipes[i][2], SDL_FLIP_VERTICAL);
		graphics.renderTexture(pipe, pipes.pos_pipes[i][0], pipes.pos_pipes[i][1]);
		if (pipes.pos_pipes[i][1] + pipes.pipeH < SCREEN_HEIGHT) {
			graphics.advancedRenderTexture(pipe, pipes.pos_pipes[i][0], pipes.pos_pipes[i][1] + pipes.pipeH, SDL_FLIP_VERTICAL);
		}

		if (pipes.pos_pipes[i][2] > 0) {
			graphics.renderTexture(pipe, pipes.pos_pipes[i][0], pipes.pos_pipes[i][2] - pipes.pipeH);
		}
	}

	pipes.scoreMeter -= pipeSpeed;

	if (gen) {
		if (pipes.pos_pipes[0][0] + pipes.pipeW < 0) {
			for (int i = 0; i < 3; i++) {
				pipes.pos_pipes[i] = pipes.pos_pipes[i + 1];
			}
			pipes.randomPositionGenerator();
			pipes.pos_pipes[3][0] = pipes.pos_pipes[2][0] + pipes.pipeW + pipes.pipeDistance;
			pipes.pos_pipes[3][1] = pipes.pipe1Y;
			pipes.pos_pipes[3][2] = pipes.pipe2Y;
		}
	}
}

void startGameSetUp(Pipe& pipes) {
	for (int i = 0; i < 4; i++) {
		pipes.randomPositionGenerator();
		pipes.pos_pipes[i][0] = SCREEN_WIDTH;
		pipes.pos_pipes[i][1] = pipes.pipe1Y;
		pipes.pos_pipes[i][2] = pipes.pipe2Y;
		if (i > 0) {
			pipes.pos_pipes[i][0] = pipes.pos_pipes[i - 1][0] + pipes.pipeW + pipes.pipeDistance;
		}
		pipes.scoreMeter = SCREEN_WIDTH + pipes.pipeW / 2;
	}
}

void resetGame(Bird& bird) {
	cout << "Score: " << bird.score << endl;
	bird.birdPosX = SCREEN_WIDTH / 5;
	bird.birdPosY = SCREEN_HEIGHT /3;
	bird.vel = 0;
	bird.score = 0;
}

void checkCollision(Pipe& pipes, Bird& bird, bool& game) {
	int boundingPosX1 = bird.birdPosX, boundingPosY1 = bird.birdPosY;
	int boundingPosX2 = boundingPosX1 + bird.widthBird, boundingPosY2 = boundingPosY1 + bird.heightBird;

	if ((boundingPosX1 + boundingPosX2) / 2 > pipes.scoreMeter) {
		bird.score += 1;
		pipes.scoreMeter += pipes.pipeW + pipes.pipeDistance;
	}

	SDL_Rect birdRect = { bird.birdPosX, bird.birdPosY, bird.widthBird, bird.heightBird };

	for (int i = 0; i < 4; i++) {
		SDL_Rect pipe1Rect = { pipes.pos_pipes[i][0], pipes.pos_pipes[i][1], pipes.pipeW, pipes.pipeH };
		SDL_Rect pipe2Rect = { pipes.pos_pipes[i][0], pipes.pos_pipes[i][2], pipes.pipeW, pipes.pipeH };
	
		if (SDL_HasIntersection(&birdRect, &pipe1Rect) || SDL_HasIntersection(&birdRect, &pipe2Rect)) {
			game = false;
			return;
		}
	}

	if (boundingPosY1 < 0) {
		game = false;
		return;
	}

	if (boundingPosY2 > SCREEN_HEIGHT) {
		game = false;
		return;
	}
}