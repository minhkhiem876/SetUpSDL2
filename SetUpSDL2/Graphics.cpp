#include "Graphics.h"
#include "Resource.h"
#include "Logic.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include "Objects.h"
using namespace std;
void ScrollingBackground::setTexture(SDL_Texture* _texture) {
	texture = _texture;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void ScrollingBackground::scroll(int distance) {
	scrollingOffSet -= distance;
	if (scrollingOffSet < -width) scrollingOffSet = 0;
}

void Graphics::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL_INIT ERROR: %s", SDL_GetError());
	}

	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		SDL_Log("Create Window ERROR: %s", SDL_GetError());
	}

	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
		SDL_Log("IMG_Init ERROR: %s", SDL_GetError());
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if (!renderer) {
		SDL_Log("CreateRenderer ERROR: %s", SDL_GetError());
	}

	if (TTF_Init() == -1) {
		SDL_Log("TTF_Init failed: %s", TTF_GetError());
	}
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Graphics::prepareScene(SDL_Texture* background) const {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
}

void Graphics::prepareSceneNoBg() const {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Graphics::presentScene() const {
	SDL_RenderPresent(renderer);
}

SDL_Texture* Graphics::loadTexture(const char* filename) const {
	SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
	if (!texture) {
		SDL_Log("LoadTexture ERROR: %s", SDL_GetError());
	}
	return texture;
}

void Graphics::renderTexture(SDL_Texture* texture, int x, int y) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}
// dest là hình chu nhat mà texture duoc ve trên renderer
// texture luôn duoc lay toan phan 

void Graphics::renderTextureAngle(SDL_Texture* texture, Bird& bird) {
	SDL_Rect dest;
	dest.x = bird.birdPosX;
	dest.y = bird.birdPosY;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_Point center = { dest.w / 2, dest.h / 2 };
	SDL_RenderCopyEx(renderer, texture, nullptr, &dest, -bird.birdAngle, &center, SDL_FLIP_NONE);
}

void Graphics::advancedRenderTexture(SDL_Texture* texture, int x, int y, SDL_RendererFlip flipType) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopyEx(renderer, texture, NULL, &dest, 0, NULL, flipType);
}

void Graphics::renderScrollBg(const ScrollingBackground& bgr) const {
	renderTexture(bgr.texture, bgr.scrollingOffSet, 0);
	renderTexture(bgr.texture, bgr.scrollingOffSet + bgr.width, 0);
}

void Graphics::quit() const {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* Graphics::renderText(const char* text, TTF_Font* font, SDL_Color textColor) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
	if (textSurface == nullptr) {
		SDL_Log("TTF_Error: %s", TTF_GetError());
		return nullptr;
	}
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (textTexture == nullptr) {
		SDL_Log("TTF_Error: %s", TTF_GetError());
		return nullptr;
	}
	return textTexture;
}

TTF_Font* Graphics::loadFont(const char* path, int size) {
	TTF_Font* font = TTF_OpenFont(path, size);
	if (font == nullptr) {
		SDL_Log("TTF_Error: %s", SDL_GetError());
		return nullptr;
	}
	return font;
}

Slider::Slider(int minV, int maxV, int initV) {
	minValue = minV;
	maxValue = maxV;
	value = initV;
}

void Slider::increase() {
	if (value < maxValue) value++;
}

void Slider::decrease() {
	if (value > minValue) value--;
}

float Slider::getPercent() const {
	return float(value - minValue) / (maxValue - minValue);
}

Button::Button(const string& label_, SDL_Rect rect_, bool isSelected_) {
	label = label_;
	rect = rect_;
	isSelected = isSelected_;
}

void Button :: render(Graphics& graphics, TTF_Font* font, TTF_Font* fontSelected, SDL_Color color) const {
	TTF_Font* usedFont = isSelected ? fontSelected : font;
	SDL_Texture* textTex = graphics.renderText(label.c_str(), usedFont, color);
	if (textTex) {
		int texW, texH;
		SDL_QueryTexture(textTex, NULL, NULL, &texW, &texH);
		SDL_Rect renderRect = rect;
		renderRect.w = texW;
		renderRect.h = texH;

		SDL_RenderCopy(graphics.renderer, textTex, NULL, &renderRect);
		SDL_DestroyTexture(textTex);
	}
}

void Menu::loadFonts(Graphics& graphics, const char* fontPath) {
	font = graphics.loadFont(fontPath, 28);
	selectedFont = graphics.loadFont(fontPath, 36);
}

void Menu::initButton() {
	mainButtons.clear();
	mainButtons.push_back({ "Play", {100, 200, 200, 50}, true });
	mainButtons.push_back({ "Settings", {100, 280, 200, 50}, false });
}

void Menu::nextChoice() {
	if (inSettings) {
		selectedChoice = (selectedChoice + 1) % 2;
	}
	else {
		mainButtons[selectedChoice].isSelected = false;
		selectedChoice = (selectedChoice + 1) % mainButtons.size();
		mainButtons[selectedChoice].isSelected = true;
	}
}

void Menu::prevChoice() {
	if (inSettings) {
		selectedChoice = (selectedChoice + 1) % 2;
	}
	else {
		mainButtons[selectedChoice].isSelected = false;
		selectedChoice = (selectedChoice - 1 + mainButtons.size()) % mainButtons.size();
		mainButtons[selectedChoice].isSelected = true;
	}
}

void Menu::drawSlider(Graphics& graphics, const char* label, int value, float percent, int x, int y, bool selected) {
	TTF_Font* usedFont = selected ? selectedFont : font;
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Color textSelectedColor = { 255, 255, 0, 255 };
	string text = string(label) + ": " + to_string(value);

	SDL_Texture* textTex = graphics.renderText(text.c_str(), usedFont, selected ? textSelectedColor : textColor);
	if (textTex) {
		int texW, texH;
		SDL_QueryTexture(textTex, NULL, NULL, &texW, &texH);

		SDL_Rect textRect = { x, y, texW, texH };

		SDL_RenderCopy(graphics.renderer, textTex, NULL, &textRect);

		SDL_DestroyTexture(textTex);
	}
	const int sliderWidth = 200;
	const int sliderHeight = 10;
	const int sliderX = x + 300;
	const int sliderY = y + 25;

	SDL_Rect sliderBack = { sliderX, sliderY, sliderWidth, sliderHeight };
	SDL_Rect sliderFill = { sliderX, sliderY, static_cast<int>(sliderWidth * percent), sliderHeight };

	SDL_SetRenderDrawColor(graphics.renderer, 100, 100, 100, 255); //xám
	SDL_RenderFillRect(graphics.renderer, &sliderBack);

	SDL_SetRenderDrawColor(graphics.renderer, 0, 200, 0, 255);//xanh
	SDL_RenderFillRect(graphics.renderer, &sliderFill);

	SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 255);//trắng 
	SDL_RenderDrawRect(graphics.renderer, &sliderBack);
}

void Menu::handleEvent(SDL_Event& event, bool& game, int& pipeSpeed, AnimationBird aniBird, Pipe& pipes, Bird& bird, bool& prepareGame) {
	if (event.type != SDL_KEYDOWN) return;

	switch (event.key.keysym.sym) {
	case SDLK_DOWN:
		nextChoice();
		break;

	case SDLK_UP:
		prevChoice();
		break;

	case SDLK_LEFT:
		if (inSettings) {
			if (selectedChoice == 0) pipeSpeedSlider.decrease();
			else if (selectedChoice == 1) passHoleSlider.decrease();
		}
		break;

	case SDLK_RIGHT:
		if (inSettings) {
			if (selectedChoice == 0) pipeSpeedSlider.increase();
			else if (selectedChoice == 1) passHoleSlider.increase();
		}
		break;

	case SDLK_RETURN:
		if (!inSettings) {
			if (selectedChoice == 0) {
				pipeSpeed = pipeSpeedSlider.value;
				pipes.passHole = passHoleSlider.value;
				prepareGame = false;
				aniBird.reset();
				resetGame(bird);
				startGameSetUp(pipes);
			}
			else if (selectedChoice == 1) {
				inSettings = true;
				selectedChoice = 0;
			}
		}
		else {
			inSettings = false;
			selectedChoice = 0;
			mainButtons[0].isSelected = true;
			mainButtons[1].isSelected = false;
		}
		break;
	}
}

void Menu::render(Graphics& graphics) {
	graphics.prepareSceneNoBg();

	SDL_Color normalColor = { 255, 255, 255, 255 };
	SDL_Color selectedColor = { 255, 255, 0, 255 };
	SDL_Color shadowColor = { 0, 0, 0, 255 };

	if (!inSettings) {
		for (int i = 0; i < mainButtons.size(); ++i) {
			Button& btn = mainButtons[i];

			SDL_Texture* shadow = graphics.renderText(
				btn.label.c_str(), font, shadowColor);
			graphics.renderTexture(shadow, btn.rect.x + 2, btn.rect.y + 2);
			SDL_DestroyTexture(shadow);

			SDL_Texture* text = graphics.renderText(btn.label.c_str(), btn.isSelected ? selectedFont : font, btn.isSelected ? selectedColor : normalColor);

			if (btn.isSelected) {
				graphics.renderTexture(text, btn.rect.x - 10, btn.rect.y - 5);
			}
			else {
				graphics.renderTexture(text, btn.rect.x, btn.rect.y);
			}

			SDL_DestroyTexture(text);
		}
	}
	else {
		drawSlider(graphics, "Pipe Speed", pipeSpeedSlider.value, pipeSpeedSlider.getPercent(), 100, 150, selectedChoice == 0);
		drawSlider(graphics, "Pass Hole", passHoleSlider.value, passHoleSlider.getPercent(), 100, 230, selectedChoice == 1);
	}
}