#include <cmath>
#include "Ennemi.h"
#include <iostream>

using namespace std;

Ennemi::Ennemi() {
    pos.x = 0;
    pos.y = 0;
    vie = 100;
    vitesse = 1;
    largeur = 1;
    hauteur = 1;
    typeEnnemi = "zombie";
    distance = false;
}

Ennemi::Ennemi(float x, float y, string type, bool attaqueDistance, int pv, float vit, int larg, int haut) {
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
    float centreEnnemiX = pos.x + largeur / 2;
    float centreEnnemiY = pos.y + hauteur / 2;

    float centreJoueurX = posJoueur.x + largeurJoueur / 2;
    float centreJoueurY = posJoueur.y + hauteurJoueur / 2;

    float dx = centreJoueurX - centreEnnemiX;
    float dy = centreJoueurY - centreEnnemiY;

    float distanceJoueur = sqrt(dx * dx + dy * dy);

    // On évite une division par 0 si l'ennemi est déjà exactement sur la cible
    if (distanceJoueur > 0) {
        float nouveauX = pos.x + (dx / distanceJoueur) * vitesse;
        float nouveauY = pos.y + (dy / distanceJoueur) * vitesse;

        Rectangle futurRect = getRectangleAvecPosition(nouveauX, nouveauY);

        Rectangle rectJoueur;
        rectJoueur.x = posJoueur.x;
        rectJoueur.y = posJoueur.y;
        rectJoueur.largeur = largeurJoueur;
        rectJoueur.hauteur = hauteurJoueur;

        // Si l'ennemi toucherait le joueur, il s'arrête juste avant
        if (!collisionRectangles(futurRect, rectJoueur)) {
            pos.x = nouveauX;
            pos.y = nouveauY;
        }
    }
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

Rectangle Ennemi::getRectangle() const {
    Rectangle r;
    r.x = pos.x;
    r.y = pos.y;
    r.largeur = largeur;
    r.hauteur = hauteur;
    return r;
}

Rectangle Ennemi::getRectangleAvecPosition(float x, float y) const {
    Rectangle r;
    r.x = x;
    r.y = y;
    r.largeur = largeur;
    r.hauteur = hauteur;
    return r;
}