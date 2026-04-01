#ifndef JEUSDL_H
#define JEUSDL_H

#include <SDL2/SDL.h>
#include "../Jeu.h"

using namespace std;

float calculerAngleDegres(const Jeu& jeu, int sourisX, int sourisY);
void afficherJeuSDL(SDL_Renderer* rendu, const Jeu& jeu);
void BoucleSDL(Jeu& jeu);

#endif 