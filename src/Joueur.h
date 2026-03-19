#ifndef JOUEUR_H
#define JOUEUR_H

#include "Position.h"
#include "Arme.h"
#include <SDL2/SDL.h>
#include <vector>
#include "Ennemi.h"

using namespace std;

class Joueur {
private:
    Position pos;
    int vie;
    float vitesse;
    int largeur;
    int hauteur;
    Arme arme;

public:
    Joueur();

    void seDeplacer(const Uint8* etatClavier, int largeurCarte, int hauteurCarte, const vector<Ennemi>& ennemis);

    Position getPosition() const;
    int getVie() const;
    int getLargeur() const;
    int getHauteur() const;

    SDL_Rect getRect() const;
    SDL_Rect getRectAvecPosition(float x, float y) const;

    void tirer();
};

#endif 