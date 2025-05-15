#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_ttf.h>
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

	SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor);

	TTF_Font* loadFont(const char* path, int size);
};

struct Slider {
	int value;
	int minValue;
	int maxValue;
	
	Slider(int minV, int maxV, int initV);
	void increase();
	void decrease();

	float getPercent() const;
};

struct Button {
	SDL_Rect rect;
	string label;
	bool isSelected = false;

	Button(const string& label_, SDL_Rect rect_, bool isSelected_);
	void render(Graphics& graphcis, TTF_Font* font, TTF_Font* fontSelected, SDL_Color color) const;
};


struct Menu {
	bool isActive = true;
	bool inSettings = false;
	int selectedChoice = 0;
	TTF_Font* font = nullptr;
	TTF_Font* selectedFont = nullptr;

	vector<Button> mainButtons;
	Slider pipeSpeedSlider = Slider(3, 13, 8);
	Slider passHoleSlider = Slider(150, 400, 200);

	void loadFonts(Graphics& graphics, const char* fontPath);
	void initButton();
	void nextChoice();
	void prevChoice();

	void drawSlider(Graphics& graphics, const char* label, int value, float percent, int x, int y, bool selected);
	void handleEvent(SDL_Event& event, bool& game, int& pipeSpeed, int& PASS_HOLE, AnimationBird aniBird, Pipe& pipes, Bird& bird, bool prepareGame);
	void render(Graphics& graphics);
};

#endif