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
    TTF_Font* police;

    float calculerAngleJoueurVersSouris(int sourisX, int sourisY) const;
    void afficherTexte(const string& texte, int x, int y) const;
    SDL_FRect convertirRect(const Rectangle& r) const;

public:
    JeuSDL();

    void afficher() const;
    void afficherChoixAmeliorations() const;
    
    void boucle();
};

#endif