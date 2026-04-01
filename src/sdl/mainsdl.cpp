#define SDL_MAIN_HANDLED
#include "JeuSDL.h"

int main() {
    Jeu jeu(1920, 1080);
    BoucleSDL(jeu);
    return 0;
}