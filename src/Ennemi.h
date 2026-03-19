#ifndef ENNEMI_H
#define ENNEMI_H

#include "Position.h"
#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Ennemi {
private:
    Position pos;
    int vie;
    float vitesse;
    int largeur;
    int hauteur;
    string typeEnnemi;
    bool distance;

public:
    Ennemi();

    void initialiser(float x, float y, string type, bool attaqueDistance, int pv, float vit, int larg, int haut);
    void seDeplacerVersJoueur(const Position& posJoueur, int largeurJoueur, int hauteurJoueur);

    Position getPosition() const;
    int getVie() const;
    int getLargeur() const;
    int getHauteur() const;
    string getTypeEnnemi() const;
    bool estDistance() const;

    SDL_Rect getRect() const;

    void attaquer();
};

#endif 