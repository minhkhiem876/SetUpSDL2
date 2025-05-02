#include "Graphics.h"
#include "Resource.h"

void ScrollingBackground::setTexture(SDL_Texture* _texture) {
	texture = _texture;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void ScrollingBackground::scroll(int distance) {
	scrollingOffSet -= distance;
	if (scrollingOffSet < -width) scrollingOffSet = 0;
}

