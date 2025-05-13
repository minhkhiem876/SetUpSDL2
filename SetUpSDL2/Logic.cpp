#include "Logic.h"
#include <iostream>
#include <SDL.h>
#include<vector>
#include "Resource.h"
void waitUntilKeyPressed()
{
	SDL_Event e;
	while (true) {
		if (SDL_PollEvent(&e) != 0 &&
			(e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
			return;
		SDL_Delay(100);
	}
}

void birdFly(const Uint8* currentKeyStated, bool& game, Bird& bird) {
	if (currentKeyStated[SDL_SCANCODE_SPACE]) {
		bird.fly = true;
		bird.timeAccel = FALL_SPEED;
	}

	if (bird.fly) {
		if (bird.timeAccel >= 0) {
			bird.timeAccel--;
		}
		if (currentKeyStated[SDL_SCANCODE_SPACE]) {
			bird.timeAccel = FALL_SPEED;
		}

		bird.birdPosY -= bird.timeAccel;

		if (bird.timeAccel == 0) {
			bird.fly = false;
		}
	}

	if (!bird.fly) {
		if (bird.timeAccel <= 2 * FALL_SPEED) {
			bird.timeAccel++;
		}
		bird.birdPosY += 2 * bird.timeAccel;
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
	bird.birdPosY = SCREEN_HEIGHT / 3;
	bird.timeAccel = 0;
	bird.score = 0;
	bird.fly = false;
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