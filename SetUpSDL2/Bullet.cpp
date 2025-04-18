#include "Bullet.h" 

Bullet::Bullet(float startX_, float startY_, float velX_, float velY_) {
	startX = startX_;
	startY = startY_;
	velX = velX_;
	velY = velY_;
}

void Bullet::updatePositionOfBullet() {
	startX += velX;
	startY += velY;
}

void Bullet::render(SDL_Renderer* rendererBullet) {
	SDL_SetRenderDrawColor(rendererBullet, 255, 0, 0, 255);
	//  (ptr, red, green, blue, weak -> light)
	SDL_Rect bulletRect = { (int)startX, (int)startY, 10, 10 };
	// ( para1, para2 are corrdinates of bullet, para3 is width and para4 is height;
	// I want to and will fix the buleet into circle later;
	SDL_RenderFillRect(rendererBullet, &bulletRect);
	// fill color of bullet to bulletRect;
}