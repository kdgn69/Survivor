#include <iostream>
#include "Ennemi.h"

using namespace std;

Ennemi::Ennemi() {
    pos.x = 0;
    pos.y = 0;
    vie = 100;
    vitesse = 0;
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
    r.x = (int) pos.x;
    r.y = (int) pos.y;
    r.w = largeur;
    r.h = hauteur;
    return r;
}

void Ennemi::seDeplacerVersJoueur() {

}

void Ennemi::attaquer() {

}