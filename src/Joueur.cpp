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

    if (direction == 'z') {
        nouveauY -= vitesse;
    }
    if (direction == 's') {
        nouveauY += vitesse;
    }
    if (direction == 'q') {
        nouveauX -= vitesse;
    }
    if (direction == 'd') {
        nouveauX += vitesse;
    }

    // On empêche le joueur de sortir de la carte

    if (nouveauX < 0) {
        nouveauX = 0;
    }
    if (nouveauY < 0) {
        nouveauY = 0;
    }
    if (nouveauX + largeur > largeurCarte) {
    nouveauX = largeurCarte - largeur;
    }
    if (nouveauY + hauteur > hauteurCarte) {
    nouveauY = hauteurCarte - hauteur;
    }

    Rectangle futurRect = getRectangleAvecPosition(nouveauX, nouveauY);
    bool collision = false;

    for (unsigned int i = 0; i < ennemis.size(); i++) {
        Rectangle rectEnnemi = ennemis[i].getRectangle();
        if (collisionRectangles(futurRect, rectEnnemi)) {
            collision = true;
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
    r.x = pos.x;
    r.y = pos.y;
    r.largeur = largeur;
    r.hauteur = hauteur;
    return r;
}

Rectangle Joueur::getRectangleAvecPosition(float x, float y) const {
    Rectangle r;
    r.x = x;
    r.y = y;
    r.largeur = largeur;
    r.hauteur = hauteur;
    return r;
}