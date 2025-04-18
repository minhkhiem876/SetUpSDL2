#include<SDL.h> 
#include<vector>
#include<iostream>
#include "Bullet.h"
#include "Wall.h" 
#include "Goal.h"
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
	// cần tạo tường, đạn, điểm đích, nhân vật 
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Không thể khởi tạo SDL!. SDL Error: " << SDL_GetError();
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Game Bắn Súng", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	// para2, para3 chính là vị trí mà cửa sổ được khởi tạo. para5 để chắc chắn cửa sổ được hiển thị

	// nếu tạo của sổ thất bại, window sẽ là nullptr do SDL_CreateWindow trả về
	if (window == nullptr) {
		cout << "Không thể tạo của sổ! SDL_Error: " << SDL_GetError();
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}


}

