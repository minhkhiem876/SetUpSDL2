#include "Graphics.h"
#include "Resource.h"
#include<SDL.h>
using namespace std;
void ScrollingBackground::setTexture(SDL_Texture* _texture) {
	texture = _texture;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void ScrollingBackground::scroll(int distance) {
	scrollingOffSet -= distance;
	if (scrollingOffSet < -width) scrollingOffSet = 0;
}

void Graphics::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL_INIT ERROR: %s", SDL_GetError());
	}

	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		SDL_Log("Create Window ERROR: %s", SDL_GetError());
	}

	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
		SDL_Log("IMG_Init ERROR: %s", SDL_GetError());
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if (!renderer) {
		SDL_Log("CreateRenderer ERROR: %s", SDL_GetError());
	}

	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Graphics::prepareScene(SDL_Texture* background) const {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
}

void Graphics::prepareSceneNoBg() const {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Graphics::presentScene() const {
	SDL_RenderPresent(renderer);
}

SDL_Texture* Graphics::loadTexture(const char* filename) const {
	SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
	if (!texture) {
		SDL_Log("LoadTexture ERROR: %s", SDL_GetError());
	}
	return texture;
}

void Graphics::renderTexture(SDL_Texture* texture, int x, int y) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}
// dest là hình chu nhat mà texture duoc ve trên renderer
// texture luôn duoc lay toan phan 

void Graphics::advancedRenderTexture(SDL_Texture* texture, int x, int y, SDL_RendererFlip flipType) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopyEx(renderer, texture, NULL, &dest, 180, NULL, flipType);
}

void Graphics::renderScrollBg(const ScrollingBackground& bgr) const {
	renderTexture(bgr.texture, bgr.scrollingOffSet, 0);
	renderTexture(bgr.texture, bgr.scrollingOffSet + bgr.width, 0);
}

void Graphics::quit() const {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}