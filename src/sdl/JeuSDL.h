#ifndef JEUSDL_H
#define JEUSDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Jeu.h"
#include "Image.h"

using namespace std;

class JeuSDL {
private:
    Jeu jeu;

    SDL_Window* fenetre;
    SDL_Renderer* rendu;
    TTF_Font* police;

    Image im_auraMorts;
    Image im_joueur;
    Image im_degats;
    Image im_cadence;
    Image im_taille;
    Image im_vitesseProjectile;
    Image im_vitesseJoueur;
    Image im_multitir;
    Image im_auraMort;
    Image im_tirPerforant;
    Image im_auraJoueur;
    Image im_foudre;
    Image im_fondNiv1;
    Image im_zoneSoin;

public:
    JeuSDL();
    ~JeuSDL();

    void afficher();
    void afficherChoixAmeliorations();
    void boucle();
};

#endif 