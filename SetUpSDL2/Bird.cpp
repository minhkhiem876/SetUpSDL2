#include "Bird.h"
#include<SDL.h>

Bird :: Bird(SDL_Renderer* renderer, const char* imagePath, int x, int y, int width, int height) {
	SDL_Surface* birdSurface = IMG_Load(imagePath);
	if (birdSurface == nullptr) {
		cout << "Can't download image of bird. Error: " << IMG_GetError() << endl;
		texture = nullptr;
		return;
	}
	texture = SDL_CreateTextureFromSurface(renderer, birdSurface);
	if (texture == nullptr) {
		cout << "Can't create texture from surface. Error: " << SDL_GetError() << endl;
		SDL_FreeSurface(birdSurface);
		return;
	}
	SDL_FreeSurface(birdSurface);
	position = { x, y, width, height };
	angle = 0.0;
}

Bird :: ~Bird() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
}

void Bird::render(SDL_Renderer* renderer) {
	SDL_RenderCopyEx(renderer, texture, NULL, &position, angle, NULL, SDL_FLIP_NONE);
}

void Bird::rotate(double deltaAngle) {
	angle += deltaAngle;
}






