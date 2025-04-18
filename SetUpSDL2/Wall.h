#ifndef WALL_H
#define WALL_H

#include<SDL.h>

class Wall {
private:
	float posX, posY, width, height;
public:
	Wall(float posX_, float posY_, float width_, float height_);
	void render(SDL_Renderer* renderer);
};

#endif