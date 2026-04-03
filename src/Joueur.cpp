#include "Joueur.h"
#include "Ennemi.h"
#include <iostream>

using namespace std;

Joueur::Joueur() {
    vie = 100;
    vitesse = 3;
    largeur = 20;
    hauteur = 20;

    pos.x = 0;
    pos.y = 0;
}

void Joueur::setPosition(float x, float y) {
    pos.x = x;
    pos.y = y;
}

void Joueur::deplacerAvecDirection(char direction, int largeurCarte, int hauteurCarte, const vector<Ennemi>& ennemis) {
    float nouveauX = pos.x;
    float nouveauY = pos.y;

    if (direction == 'z') nouveauY -= vitesse;
    if (direction == 's') nouveauY += vitesse;
    if (direction == 'q') nouveauX -= vitesse;
    if (direction == 'd') nouveauX += vitesse;

    // On empêche le joueur de sortir de la carte
    float demiLargeur = largeur / 2.;
    float demiHauteur = hauteur / 2.;

    if (nouveauX - demiLargeur < 0) {
        nouveauX = demiLargeur;
    }
    if (nouveauY - demiHauteur < 0) {
        nouveauY = demiHauteur;
    }
    if (nouveauX + demiLargeur > largeurCarte) {
        nouveauX = largeurCarte - demiLargeur;
    }
    if (nouveauY + demiHauteur > hauteurCarte) {
        nouveauY = hauteurCarte - demiHauteur;
    }

    Rectangle futurRect = getRectangleAvecPosition(nouveauX, nouveauY);
    bool collision = false;

    for (unsigned int i = 0; i < ennemis.size(); i++) {
        Rectangle rectEnnemi = ennemis[i].getRectangle();
        if (collisionRectangles(futurRect, rectEnnemi)) {
            collision = true;
            break;
        }
    }

    if (!collision) {
        pos.x = nouveauX;
        pos.y = nouveauY;
    }
}

Position Joueur::getPosition() const {
    return pos;
}

int Joueur::getVie() const {
    return vie;
}

int Joueur::getLargeur() const {
    return largeur;
}

int Joueur::getHauteur() const {
    return hauteur;
}

Rectangle Joueur::getRectangle() const {
    Rectangle r;
    r.x = pos.x - largeur / 2;
    r.y = pos.y - hauteur / 2;
    r.largeur = largeur;
    r.hauteur = hauteur;
    return r;
}

Rectangle Joueur::getRectangleAvecPosition(float centreX, float centreY) const {
    Rectangle r;
    r.x = centreX - largeur / 2;
    r.y = centreY - hauteur / 2;
    r.largeur = largeur;
    r.hauteur = hauteur;
    return r;
}