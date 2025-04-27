#ifndef GOAL_H
#define GOAL_H

#include<SDL.h> 

class Goal {
private:
	float startX, startY, width, height;
public: 
	Goal (float startX_, float startY_, float width_, float height_);
	void render(SDL_Renderer* rendererGoal);
};
#endif 