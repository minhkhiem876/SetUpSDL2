#include "Logic.h"
#include "Graphics.h"
#include "Resource.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


void birdFly(const Uint8* currentKeyStated, Bird& bird) {
	if (currentKeyStated[SDL_SCANCODE_SPACE]) {
		bird.vel = -FLY_SPEED;
		bird.birdAngle = bird.MIN_ANGLE;
	}

	bird.vel += 1;
	if (bird.vel > bird.MAX_DROP_SPEED) {
		bird.vel = bird.MAX_DROP_SPEED;
	}
	bird.birdPosY += bird.vel;

	if (bird.vel >= 0) {
		bird.birdAngle -= bird.ANGLE_FALL_SPEED;
		if (bird.birdAngle > bird.MAX_ANGLE) {
			bird.birdAngle = bird.MAX_ANGLE;
		}
	}
	else {
		bird.birdAngle = bird.MIN_ANGLE;
	}
}

void pipeRunning(Pipe& pipes, Graphics& graphics, SDL_Texture* pipe, const int pipeSpeed, vector<Item>& items) {
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
	for (int i = 0; i < 3; i++) {
		if (items[i].isActive) {
			items[i].posX = (pipes.pos_pipes[i][0] + pipes.pos_pipes[i + 1][0] + pipes.pipeW) / 2 - items[i].width / 2;
			items[i].posY = (pipes.pos_pipes[i][1] + pipes.pos_pipes[i + 1][2] + pipes.pipeH) / 2 - items[i].height / 2;
			graphics.renderTexture(graphics.loadTexture(ITEM_PATH), items[i].posX, items[i].posY);
		}
	}

	pipes.scoreMeter -= pipeSpeed;

	if (pipes.pos_pipes[0][0] + pipes.pipeW + pipes.pipeDistance + items[1].width < 0) {
		for (int i = 0; i < 3; i++) {
			pipes.pos_pipes[i] = pipes.pos_pipes[i + 1];
			if (i != 2) {
				items[i] = items[i + 1];
				items[i].associatedPipeIndex = i;
			}
		}
		pipes.randomPositionGenerator();	
		pipes.pos_pipes[3][0] = pipes.pos_pipes[2][0] + pipes.pipeW + pipes.pipeDistance;
		pipes.pos_pipes[3][1] = pipes.pipe1Y;
		pipes.pos_pipes[3][2] = pipes.pipe2Y;

		items[2].reset((pipes.pos_pipes[2][0] + pipes.pos_pipes[3][0] + pipes.pipeW) / 2 - items[2].width / 2,
			(pipes.pos_pipes[2][1] + pipes.pos_pipes[3][2] + pipes.pipeH) / 2 - items[2].height / 2);
		int chance = rand() % 101; 
		items[2].isActive = (chance <= ITEM_DROP_CHANCE);
		items[2].associatedPipeIndex = 2;
	}
	
}

void startGameSetUp(Pipe& pipes, vector<Item>& items) {
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
	for (int i = 0; i < 3; i++) {
		items[i].reset((pipes.pos_pipes[i][0] + pipes.pos_pipes[i + 1][0] + pipes.pipeW) / 2 - items[i].width / 2,
			(pipes.pos_pipes[i][1] + pipes.pos_pipes[i + 1][2] + pipes.pipeH) / 2 - items[i].height / 2);
		int chance = rand() % 101;
		items[i].isActive = (chance <= ITEM_DROP_CHANCE);
		items[i].associatedPipeIndex = i;
	}
}

void resetGame(Bird& bird, int& lastScoreCheck) {
	cout << "Score: " << bird.score << endl;
	bird.birdPosX = SCREEN_WIDTH / 5;
	bird.birdPosY = SCREEN_HEIGHT /3;
	bird.vel = 0;
	bird.score = 0;
	bird.birdAngle = 0;
	lastScoreCheck = 0;
}

void checkCollision(Pipe& pipes, Bird& bird, bool& prepareGame, vector<Item>& items) {
	int boundingPosX1 = bird.birdPosX, boundingPosY1 = bird.birdPosY;
	int boundingPosX2 = boundingPosX1 + bird.widthBird, boundingPosY2 = boundingPosY1 + bird.heightBird;

	if ((boundingPosX1 + boundingPosX2) / 2 > pipes.scoreMeter) {
		bird.score += 1;
		pipes.scoreMeter += pipes.pipeW + pipes.pipeDistance;
	}

	SDL_Rect birdRect = { bird.birdPosX, bird.birdPosY, bird.widthBird, bird.heightBird };

	for (int i = 0; i < 3; i++) {
		if (items[i].isActive) {
			SDL_Rect itemRect = { items[i].posX, items[i].posY, items[i].width, items[i].height };
			if (SDL_HasIntersection(&birdRect, &itemRect)) {
				items[i].isActive = false;
				bird.score++;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		SDL_Rect pipe1Rect = { pipes.pos_pipes[i][0], pipes.pos_pipes[i][1], pipes.pipeW, pipes.pipeH };
		SDL_Rect pipe2Rect = { pipes.pos_pipes[i][0], pipes.pos_pipes[i][2], pipes.pipeW, pipes.pipeH };
	
		if (SDL_HasIntersection(&birdRect, &pipe1Rect) || SDL_HasIntersection(&birdRect, &pipe2Rect)) {
			prepareGame = true;
			return;
		}
	}

	if (boundingPosY1 < 0) {
		prepareGame = true;
		return;
	}

	if (boundingPosY2 > SCREEN_HEIGHT) {
		prepareGame = true;
		return;
	}
}

void renderScore(Graphics& graphics, int score, string line, TTF_Font* font, SDL_Color color, int x, int y) {
	string scored = line + to_string(score);
	SDL_Texture* scoreText = graphics.renderText(scored.c_str(), font, color);
	graphics.renderTexture(scoreText, x, y);
	SDL_DestroyTexture(scoreText);
}
