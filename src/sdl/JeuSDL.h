#ifndef JEUSDL_H
#define JEUSDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Jeu.h"

using namespace std;

class JeuSDL {
private:
    Jeu jeu;
    SDL_Window* fenetre;
    SDL_Renderer* rendu;

    float calculerAngleJoueurVersSouris(int sourisX, int sourisY) const;

public:
    JeuSDL();

    void afficher() const;
    void afficherChoixAmeliorations() const;
    void boucle();
};

#endif