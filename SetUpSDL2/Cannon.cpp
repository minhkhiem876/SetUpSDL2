#include "Cannon.h"
#include<SDL.h>

Cannon:: Cannon(SDL_Renderer* renderer, const char* imagePath, int x, int y, int width, int height) {
	SDL_Surface* cannonSurface = IMG_Load(imagePath);
	if (cannonSurface == nullptr) {
		cout << "Can't download image of cannon. Error: " << IMG_GetError() << endl;
		texture = nullptr;
		return;
	}
	texture = SDL_CreateTextureFromSurface(renderer, cannonSurface);
	if (texture == nullptr) {
		cout << "Can't create texture from surface. Error: " << SDL_GetError() << endl;
		SDL_FreeSurface(cannonSurface);
		return;
	}
	SDL_FreeSurface(cannonSurface);
	position = { x, y, width, height };
	angle = 0.0;
}

Cannon :: ~Cannon() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
}

void Cannon::render(SDL_Renderer* renderer) {
	SDL_RenderCopyEx(renderer, texture, NULL, &position, angle, NULL, SDL_FLIP_NONE);
}

void Cannon::rotate(double deltaAngle) {
	angle += deltaAngle;
}

void Cannon::move(int dx) {
	position.x += dx;
}




