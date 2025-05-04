#include <iostream>
#include <SDL.h> 
#include <SDL_image.h>
#include <vector>
#include "Graphics.h"
#include "Objects.h"
#include <ctime>
using namespace std;


int main(int argc, char* argv[]) {
	Graphics graphics;
	graphics.init();

	SDL_Texture* bgTexture = graphics.loadTexture(SKY_BACKGROUND_PATH);
	SDL_Texture* pipeTexture = graphics.loadTexture(PIPE_PATH);

	ScrollingBackground background;
	background.setTexture(bgTexture);

	Pipe pipe;
	SDL_QueryTexture(pipeTexture, NULL, NULL, &pipe.pipeW, &pipe.pipeH);
	srand(time(NULL));
	
	for (int i = 0; i < Pipe::rows; i++) {

	}
}