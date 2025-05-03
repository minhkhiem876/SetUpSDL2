#ifndef LOGIC_H
#define LOGIC_H
#include "Objects.h"

void updateBird(Bird& bird);

bool checkCollision(const Bird& bird, const Pipe& pipes);

void updatePipes(Pipe& pipes, Bird& bird);

#endif 