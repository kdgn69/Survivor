#ifndef JEUSDL_H
#define JEUSDL_H

#include <SDL2/SDL.h>
#include "../Jeu.h"

using namespace std;

// Affiche l'état du jeu en SDL
void afficherJeuSDL(SDL_Renderer* rendu, const Jeu& jeu);

// Lance la boucle complète du mode SDL
void BoucleSDL(Jeu& jeu);

#endif 