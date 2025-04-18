#include "Wall.h"
#include<SDL.h>

Wall::Wall(float posX_, float posY_, float width_, float height_) {
	posX = posX_;
	posY = posY_;
	width = width_;
	height = height_;
}

void Wall::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect wallRect = { (int)posX, (int)posY, (int)width, (int)height };
	SDL_RenderFillRect(renderer, &wallRect);
}