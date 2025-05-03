#ifndef GRAPHICS_H
#define GRAPHICS_H

#include<SDL.h>
#include<SDL_image.h>
#include<vector>
using namespace std;

struct ScrollingBackground {
	SDL_Texture* texture;
	int scrollingOffSet = 0;
	int width, height;

	void setTexture(SDL_Texture* _texture);
	void scroll(int distance);
};

struct Graphics {
	SDL_Renderer* renderer;
	SDL_Window* window;

	void init();
	void prepareScene(SDL_Texture* background);
	void presentScene();
	SDL_Texture* loadTexture(const char* filename);
	void renderTexture(SDL_Texture* texture, int x, int y);
	void renderScrollBg(const ScrollingBackground& bg);
	void quit();
};




#endif