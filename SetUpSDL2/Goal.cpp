#include"Goal.h"
#include<SDL.h>

Goal :: Goal (float startX_, float startY_, float width_, float height_) {
	startX = startX_;
	startY = startY_;
	width = width_;
	height = height_;
}

void Goal::render(SDL_Renderer* rendererGoal) {
	SDL_SetRenderDrawColor(rendererGoal, 255, 255, 255, 255);
	SDL_Rect goalRect = { (int)startX, (int)startY, 7, 7 };
	SDL_RenderFillRect(rendererGoal, &goalRect);
}

