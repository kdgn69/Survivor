#ifndef JEUSDL_H
#define JEUSDL_H

#include "../Jeu.h"

using namespace std;

void renderSDL(SDL_Renderer* rendu);
void updateSDL(const Uint8* etatClavier);
void Boucle(Jeu& jeu);
#endif