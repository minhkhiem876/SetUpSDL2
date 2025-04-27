#ifndef BULLET_H
#define BULLET_H	

#include <SDL.h>

class Bullet {
public:
	float startX, startY, velX, velY;

	Bullet (float startX_, float startY_, float velX_, float velY_);
	void updatePositionOfBullet();
	void render(SDL_Renderer* renderBullet);
};
#endif 