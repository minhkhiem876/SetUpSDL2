#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include "Objects.h"
#include <SDL_image.h>
#include <vector>
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

	void prepareScene(SDL_Texture* background) const;

	void prepareSceneNoBg() const;

	void presentScene() const;

	SDL_Texture* loadTexture(const char* filename) const;

	void renderTexture(SDL_Texture* texture, int x, int y) const;

	void renderTextureAngle(SDL_Texture* texture, Bird& bird);

	void advancedRenderTexture(SDL_Texture* texture, int x, int y, SDL_RendererFlip flipType) const;

	void renderScrollBg(const ScrollingBackground& bg) const;

	void quit() const;

};

#endif