#ifndef CANNON_H
#define CANNON_H
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<vector>
using namespace std;

class Cannon {
private:
	SDL_Texture* texture;
	SDL_Rect position;
	double angle;
public:
	Cannon(SDL_Renderer* renderer, const char* imagePath, int x, int y, int width, int height);
	~Cannon();
	void render(SDL_Renderer* renderer);
	void rotate(double deltaAngle);
	void move(int dx);
};

#endif