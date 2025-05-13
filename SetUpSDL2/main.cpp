#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Resource.h"
#include "Graphics.h"
#include "Objects.h"
#include "Logic.h"
#include <ctime>
using namespace std;

int main(int argc, char* agrv[]) {
	Graphics graphics;
	graphics.init();
	SDL_Color color = { 255, 255, 0, 0 };

	ScrollingBackground background;
	background.setTexture(graphics.loadTexture(SKY_BACKGROUND_PATH));
	SDL_Texture* birdTexture = graphics.loadTexture(BIRD_PATH);
	SDL_Texture* pipeTexture = graphics.loadTexture(PIPE_PATH);

	AnimationBird aniBird;
	Bird bird;
	Pipe pipes;
	SDL_QueryTexture(pipeTexture, NULL, NULL, &pipes.pipeW, &pipes.pipeH);
	SDL_QueryTexture(birdTexture, NULL, NULL, &bird.widthBird, &bird.heightBird);
	aniBird.loadFrame(graphics.renderer);

	srand(time(NULL));
	bool quit = false, prepareGame = true, firstPlay = true, game = false;
	int highScore = 0, timer = 0;

	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
			else if (event.type == SDL_KEYDOWN && prepareGame) {
				if (event.key.keysym.sym == SDLK_SPACE) {
					prepareGame = false;
					resetGame(bird);
					startGameSetUp(pipes);
					game = true;
				}
			}
		}

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if (!game) {
			background.scroll(0);

			if (firstPlay) {
				graphics.prepareSceneNoBg();
				graphics.renderScrollBg(background);
				aniBird.updateBirdAnimation();
				graphics.renderTextureAngle(aniBird.birdFrames[aniBird.currentFrame], bird);
			}
			else {
				pipeRunning(pipes, graphics, pipeTexture, 0, false);
				timer += 10;
				if (timer == 200) {
					prepareGame = true;
					timer = 0;
				}
			}
		}

		else {
			graphics.prepareSceneNoBg();
			firstPlay = false;

			background.scroll(1);
			graphics.renderScrollBg(background);

			pipeRunning(pipes, graphics, pipeTexture, pipeSpeed, true);
			birdFly(currentKeyStates, bird);
			aniBird.updateBirdAnimation();
			graphics.renderTextureAngle(aniBird.birdFrames[aniBird.currentFrame], bird);
			checkCollision(pipes, bird, game);
		}
		graphics.presentScene();
	}

	graphics.quit();
	return 0;
}