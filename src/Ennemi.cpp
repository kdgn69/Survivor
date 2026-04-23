#include <cmath>
#include "Ennemi.h"

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
    float dx = posJoueur.x - pos.x;
    float dy = posJoueur.y - pos.y;

    float distanceJoueur = sqrt(dx * dx + dy * dy);

    if (distanceJoueur > 0) {
        float nouveauX = pos.x + (dx / distanceJoueur) * vitesse;
        float nouveauY = pos.y + (dy / distanceJoueur) * vitesse;

        Rectangle futurRect = getRectangleAvecPosition(nouveauX, nouveauY);

        Rectangle rectJoueur;
        rectJoueur.x = posJoueur.x - largeurJoueur / 2;
        rectJoueur.y = posJoueur.y - hauteurJoueur / 2;
        rectJoueur.largeur = largeurJoueur;
        rectJoueur.hauteur = hauteurJoueur;

        if (!collisionRectangles(futurRect, rectJoueur)) {
            pos.x = nouveauX;
            pos.y = nouveauY;
        }
    }
}

void Ennemi::prendreDegats(int degats) {
    vie -= degats;
}

bool Ennemi::estMort() const {
    return vie <= 0;
}

Position Ennemi::getPosition() const {
    return pos;
}

int Ennemi::getLargeur() const {
    return largeur;
}

int Ennemi::getHauteur() const {
    return hauteur;
}

Rectangle Ennemi::getRectangle() const {
    Rectangle r;
    r.x = pos.x - largeur / 2;
    r.y = pos.y - hauteur / 2;
    r.largeur = largeur;
    r.hauteur = hauteur;
    return r;
}

Rectangle Ennemi::getRectangleAvecPosition(float centreX, float centreY) const {
    Rectangle r;
    r.x = centreX - largeur / 2;
    r.y = centreY - hauteur / 2;
    r.largeur = largeur;
    r.hauteur = hauteur;
    return r;
}