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

	graphics.loadMusic(MUSIC_PATH);
	graphics.playMusic();

	ScrollingBackground background;
	background.setTexture(graphics.loadTexture(SKY_BACKGROUND_PATH));
	SDL_Texture* birdTexture = graphics.loadTexture(BIRD_PATH);
	SDL_Texture* pipeTexture = graphics.loadTexture(PIPE_PATH);
	SDL_Texture* itemTexture = graphics.loadTexture(ITEM_PATH);

	vector<Item> items(3);
	for (int i = 0; i < 3; i++) {
		SDL_QueryTexture(itemTexture, NULL, NULL, &items[i].width, &items[i].height);
	}

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
	int lastScoreCheck = 0;

	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
			else if (event.type == SDL_KEYDOWN && prepareGame) {
				menu.handleEvent(event, game, pipeSpeed, aniBird, pipes, bird, prepareGame, items, lastScoreCheck);
			}
		}
		
		graphics.prepareSceneNoBg();
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if (prepareGame && !game) {
			menu.render(graphics);
			aniBird.reset();
			startGameSetUp(pipes, items);
			resetGame(bird, lastScoreCheck);
		}

		else if (!prepareGame && !game) {
			background.scroll(0);
			graphics.renderScrollBg(background);
			aniBird.updateBirdAnimation();
			graphics.renderTextureAngle(aniBird.birdFrames[aniBird.currentFrame], bird);
			if (currentKeyStates[SDL_SCANCODE_SPACE]) {
				pipeRunning(pipes, graphics, pipeTexture, pipeSpeed, items);
				birdFly(currentKeyStates, bird);
				aniBird.updateBirdAnimation();
				graphics.renderTextureAngle(aniBird.birdFrames[aniBird.currentFrame], bird);
				game = true;
			}
		}

		else if (!prepareGame && game) {
			background.scroll(1);
			graphics.renderScrollBg(background);
			pipeRunning(pipes, graphics, pipeTexture, pipeSpeed, items);
			birdFly(currentKeyStates, bird);
			aniBird.updateBirdAnimation();
			graphics.renderTextureAngle(aniBird.birdFrames[aniBird.currentFrame], bird);
			checkCollision(pipes, bird, prepareGame, items);
			if (bird.score > lastScoreCheck && bird.score % 10 == 0) {
				pipeSpeed++;
				lastScoreCheck = bird.score;
			}
		}
		else {
			background.scroll(0);
			graphics.renderScrollBg(background);
			pipeRunning(pipes, graphics, pipeTexture, 0, items);
			aniBird.updateDeadAnimation(bird);
			graphics.renderTextureAngle(aniBird.birdDeadFrames[aniBird.currentDeadFrame], bird);
			timer += 10;
			if (timer >= 500) {
				game = false;
				timer = 0;
			}
		}
		highestScore = max(highestScore, bird.score);
		renderScore(graphics, bird.score, "Score: ", font, colorScore, 0, 0);
		renderScore(graphics, highestScore, "HighestScore: ", font, colorHighestScore, 0, 30);
		graphics.presentScene();
	} 

	graphics.quit(); 
	return 0;
}