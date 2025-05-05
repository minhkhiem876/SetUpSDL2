#include "Logic.h"
#include <iostream>
#include <SDL.h>
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
		bird.timeAccel = 5;

	}

	if (bird.fly) {
		if (bird.timeAccel >= 0) {
			bird.timeAccel--;
		}
		if (currentKeyStated[SDL_SCANCODE_SPACE]) {
			bird.timeAccel = 5;
		}

		bird.birdPosY -= 4 * bird.timeAccel;

		if (bird.timeAccel == 0) {
			bird.fly = false;
		}
	}

	if (!bird.fly) {
		if (bird.timeAccel <= 10) {
			bird.timeAccel++;
		}

		bird.birdPosY += 5 * bird.timeAccel;
	}
}

void pipeRunning(Pipe& pipes, Graphics& graphics, SDL_Texture* pipe, int pipeSpeed, bool gen) {
	for (int i = 0; i < 4; i++) {
		pipes.pos_pipes[i][0] -= pipeSpeed;
		graphics.renderTexture(pipe, pipes.pos_pipes[i][0], pipes.pos_pipes[i][1]);
		graphics.advancedRenderTexture(pipe, pipes.pos_pipes[i][0], pipes.pos_pipes[i][1], SDL_FLIP_HORIZONTAL);
		if (pipes.pos_pipes[i][1] + pipes.pipeH < SCREEN_HEIGHT) {
			graphics.renderTexture(pipe, pipes.pos_pipes[i][0], pipes.pos_pipes[i][1] + pipes.pipeH);
		}

		if (pipes.pos_pipes[i][2] > 0) {
			graphics.advancedRenderTexture(pipe, pipes.pos_pipes[i][0], pipes.pos_pipes[i][2] - pipes.pipeH, SDL_FLIP_HORIZONTAL);
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

void checkCollision(Pipe& pipes, Bird& bird, bool& quit) {
	int boundingPosX1 = bird.birdPosX, boundingPosY1 = bird.birdPosY;
	int boundingPosX2 = boundingPosX1 + bird.widthBird, boundingPosY2 = boundingPosY1 + bird.heightBird;

	if ((boundingPosX1 + boundingPosX2) / 2 > pipes.scoreMeter) {
		bird.score += 1;
		pipes.scoreMeter = pipes.pipeW + pipes.pipeDistance;
	}

	for (int i = 0; i < 4; i++) {
		if (pipes.pos_pipes[i][0] < boundingPosX2 && pipes.pos_pipes[i][0] + pipes.pipeW > boundingPosX1) {
			if (boundingPosY2 > pipes.pos_pipes[i][1] || boundingPosY1 < pipes.pos_pipes[i][2] + pipes.pipeH) {
				quit = true;
			}
		}
	}

	if (boundingPosY2 > SCREEN_HEIGHT) {
		quit = true;
	}
}