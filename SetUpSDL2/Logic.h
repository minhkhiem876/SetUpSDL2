#ifndef LOGIC_H
#define LOGIC_H
#include <iostream>
#include "Objects.h"
#include "Resource.h"
#include "Graphics.h"

void birdFly(const Uint8* currentKeyStated, Bird& bird);

void pipeRunning(Pipe& pipes, Graphics& graphics, SDL_Texture* pipe, const int pipeSpeed, bool gen);

void startGameSetUp(Pipe& pipes);

void resetGame(Bird& bird);

void checkCollision(Pipe& pipes, Bird& bird, bool& game);

#endif 