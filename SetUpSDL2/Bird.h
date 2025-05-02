#ifndef BIRD_H
#define BIRD_H
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<vector>
using namespace std;

class Bird {
private:
	SDL_Texture* texture;
	SDL_Rect position;
	double angle;
public:
	Bird(SDL_Renderer* renderer, const char* imagePath, int x, int y, int width, int height);
	~Bird();
	void render(SDL_Renderer* renderer);
	void rotate(double deltaAngle);
};

#endif