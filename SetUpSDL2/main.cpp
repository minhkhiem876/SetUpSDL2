#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Resource.h"
#include "Graphics.h"
#include "Objects.h"
#include "Logic.h"
#include <algorithm>
#include <ctime>
using namespace std;

int main(int argc, char* agrv[]) {
	Graphics graphics;
	graphics.init();
	SDL_Color colorScore = { 0, 200, 0, 255 };
	SDL_Color colorHighestScore = { 255, 50, 50, 255 };
	int fontSize = 20;
	TTF_Font* font = graphics.loadFont(FONT_PATH, fontSize);

	ScrollingBackground background;
	background.setTexture(graphics.loadTexture(SKY_BACKGROUND_PATH));
	SDL_Texture* birdTexture = graphics.loadTexture(BIRD_PATH);
	SDL_Texture* pipeTexture = graphics.loadTexture(PIPE_PATH);

	AnimationBird aniBird;
	Bird bird;
	Pipe pipes;
	Menu menu;
	menu.loadFonts(graphics, FONT_PATH);
	menu.initButton();
	SDL_QueryTexture(pipeTexture, NULL, NULL, &pipes.pipeW, &pipes.pipeH);
	SDL_QueryTexture(birdTexture, NULL, NULL, &bird.widthBird, &bird.heightBird);
	aniBird.loadFrame(graphics.renderer);

	srand(time(NULL));
	bool quit = false, prepareGame = true, firstPlay = true, game = false;
	int highestScore = 0, timer = 0;

	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
			else if (event.type == SDL_KEYDOWN && prepareGame) {
				menu.handleEvent(event, game, pipeSpeed, PASS_HOLE, aniBird, pipes, bird, prepareGame);
			}
		}
		
		graphics.prepareSceneNoBg();
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if (prepareGame) {
			menu.render(graphics);
		}

		else if (!game) {
			graphics.prepareSceneNoBg();
			background.scroll(0);
			graphics.renderScrollBg(background);

			if (firstPlay) {
				aniBird.updateBirdAnimation();
				graphics.renderTextureAngle(aniBird.birdFrames[aniBird.currentFrame], bird);
			}
			else {
				pipeRunning(pipes, graphics, pipeTexture, 0);
				aniBird.updateDeadAnimation(bird);
				graphics.renderTexture(aniBird.birdDeadFrames[aniBird.currentDeadFrame], bird.birdPosX, bird.birdPosY);
				timer += 10;
				if (timer == 500) {
					prepareGame = true;
					timer = 0;
				}
			}
		}

		else {
			firstPlay = false;

			background.scroll(1);
			graphics.renderScrollBg(background);

			pipeRunning(pipes, graphics, pipeTexture, pipeSpeed);
			birdFly(currentKeyStates, bird);
			aniBird.updateBirdAnimation();
			graphics.renderTextureAngle(aniBird.birdFrames[aniBird.currentFrame], bird);
			checkCollision(pipes, bird, game);
		}
		highestScore = max(highestScore, bird.score);
		renderScore(graphics, bird.score, "Score: ", font, colorScore, 0, 0);
		renderScore(graphics, highestScore, "HighestScore: ", font, colorHighestScore, 0, 30);
		graphics.presentScene();
	} 

	graphics.quit();
	return 0;
}