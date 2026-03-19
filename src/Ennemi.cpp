#include <iostream>
#include <cmath>
#include "Ennemi.h"

using namespace std;

Ennemi::Ennemi() {
    pos.x = 0;
    pos.y = 0;
    vie = 100;
    vitesse = 1;
    largeur = 30;
    hauteur = 30;
    typeEnnemi = "zombie";
    distance = false;
}

void Ennemi::initialiser(float x, float y, string type, bool attaqueDistance, int pv, float vit, int larg, int haut) {
    pos.x = x;
    pos.y = y;
    typeEnnemi = type;
    distance = attaqueDistance;
    vie = pv;
    vitesse = vit;
    largeur = larg;
    hauteur = haut;
}

void Ennemi::seDeplacerVersJoueur(const Position& posJoueur, int largeurJoueur, int hauteurJoueur) {
    float centreEnnemiX = pos.x + largeur / 2.0;
    float centreEnnemiY = pos.y + hauteur / 2.0;

    float centreJoueurX = posJoueur.x + largeurJoueur / 2.0;
    float centreJoueurY = posJoueur.y + hauteurJoueur / 2.0;

    float dx = centreJoueurX - centreEnnemiX;
    float dy = centreJoueurY - centreEnnemiY;

    float distanceJoueur = sqrt(dx * dx + dy * dy);

    if (distanceJoueur > 0) {
        float nouveauX = pos.x + (dx / distanceJoueur) * vitesse;
        float nouveauY = pos.y + (dy / distanceJoueur) * vitesse;

        SDL_Rect futurRect = getRectAvecPosition(nouveauX, nouveauY);
        SDL_Rect rectJoueur;
        rectJoueur.x = int(posJoueur.x);
        rectJoueur.y = int(posJoueur.y);
        rectJoueur.w = largeurJoueur;
        rectJoueur.h = hauteurJoueur;

        if (!SDL_HasIntersection(&futurRect, &rectJoueur)) {
            pos.x = nouveauX;
            pos.y = nouveauY;
        }
    }
}

bool Ennemi::toucheJoueur(const SDL_Rect& rectJoueur) const {
    SDL_Rect rectEnnemi = getRect();
    return SDL_HasIntersection(&rectEnnemi, &rectJoueur);
}

Position Ennemi::getPosition() const {
    return pos;
}

int Ennemi::getVie() const {
    return vie;
}

int Ennemi::getLargeur() const {
    return largeur;
}

int Ennemi::getHauteur() const {
    return hauteur;
}

string Ennemi::getTypeEnnemi() const {
    return typeEnnemi;
}

bool Ennemi::estDistance() const {
    return distance;
}

SDL_Rect Ennemi::getRect() const {
    SDL_Rect r;
    r.x = int(pos.x);
    r.y = int(pos.y);
    r.w = largeur;
    r.h = hauteur;
    return r;
}

SDL_Rect Ennemi::getRectAvecPosition(float x, float y) const {
    SDL_Rect r;
    r.x = int(x);
    r.y = int(y);
    r.w = largeur;
    r.h = hauteur;
    return r;
}

void Ennemi::attaquer() {

} 