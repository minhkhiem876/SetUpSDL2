#include<iostream>
#include<SDL.h> 
#include<SDL_image.h>
#include<vector>
#include "Bullet.h"
#include "Wall.h" 
#include "Goal.h"
#include "Bird.h"
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;

int main(int argc, char* args[]) {
	// cần tạo tường, đạn, điểm đích, nhân vật 
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { // sử dụng đồ họa và cửa sổ 
		cout << "Không thể khởi tạo SDL!. SDL Error: " << SDL_GetError();
		return -1;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) { // img_init... trả về int, cụ thể là flag đại diện cho IMG_INIT_IMAGE.
		cout << "Không thể khởi tạo SDL_image! SDL_image Error: " << IMG_GetError() << endl;
		SDL_Quit();
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Flappy Bird	", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	// para2, para3 chính là vị trí mà cửa sổ được khởi tạo. para5 để chắc chắn cửa sổ được hiển thị

	// nếu tạo của sổ thất bại, window sẽ là nullptr do SDL_CreateWindow trả về
	if (window == nullptr) {
		cout << "Không thể tạo cửa sổ! SDL_Error: " << SDL_GetError();
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		cout << "Không thể tạo được renderer! SDL_Error." << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return -1;
	}

	SDL_Surface* bgSurface = IMG_Load("C:/Users/khiem/Desktop/SetUpSDL2/SetUpSDL2/background.png");
	if (bgSurface == nullptr) {
		cout << "Không thể load ảnh background! SDL_ImageError: " << IMG_GetError() << endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return -1;
	}

	SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
	SDL_FreeSurface(bgSurface);
	if (bgTexture == nullptr) {
		std::cout << "Không thể tạo texture nền! Error: " << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return -1;
	}

	Bird bird(renderer, "C:/Users/khiem/Desktop/SetUpSDL2/SetUpSDL2/Cannon.png", 200, 300, 150, 150);
	
	bool isRunning = true;
	SDL_Event event;

	while (isRunning) {
		while (SDL_PollEvent(&event)) { // lấy sự kiện từ hàng đợi sự kiện và gán nó vào STRUCT event;
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
			else if (event.type == SDL_
			}
			SDL_RenderClear(renderer);          
			SDL_RenderCopy(renderer, bgTexture, NULL, NULL); 
			bird.render(renderer);            
			SDL_RenderPresent(renderer);       
		}
	}
}

