#ifndef LOGIC_H
#define LOGIC_H
#include <SDL_ttf.h>
#include <iostream>
#include "Objects.h"
#include "Resource.h"
#include "Graphics.h"
using namespace std;

void birdFly(const Uint8* currentKeyStated, Bird& bird);

void pipeRunning(Pipe& pipes, Graphics& graphics, SDL_Texture* pipe, const int pipeSpeed, vector<Item>& items);

void startGameSetUp(Pipe& pipes, vector<Item>& items);

void resetGame(Bird& bird, int& lastScoreCheck);

void checkCollision(Pipe& pipes, Bird& bird, bool& prepareGame, vector<Item>& items);

void renderScore(Graphics& graphics, int score, string line, TTF_Font* font, SDL_Color color, int x, int y);


#endif 