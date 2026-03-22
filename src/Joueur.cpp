#include <iostream>
#include "Joueur.h"
#include "Ennemi.h"

using namespace std;

const int LARGEUR_CARTE_DEFAUT = 40;
const int HAUTEUR_CARTE_DEFAUT = 20;

Joueur::Joueur() {
    vie = 100;
    vitesse = 1;
    largeur = 1;
    hauteur = 1;

    pos.x = LARGEUR_CARTE_DEFAUT / 2;
    pos.y = HAUTEUR_CARTE_DEFAUT / 2;
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

    if (nouveauX < 0) {
        nouveauX = 0;
    }
    if (nouveauY < 0) {
        nouveauY = 0;
    }
    if (nouveauX >= largeurCarte) {
        nouveauX = largeurCarte - 1;
    }
    if (nouveauY >= hauteurCarte) {
        nouveauY = hauteurCarte - 1;
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
    r.x = int(pos.x);
    r.y = int(pos.y);
    r.largeur = largeur;
    r.hauteur = hauteur;
    return r;
}

Rectangle Joueur::getRectangleAvecPosition(float x, float y) const {
    Rectangle r;
    r.x = int(x);
    r.y = int(y);
    r.largeur = largeur;
    r.hauteur = hauteur;
    return r;
}

void Joueur::tirer() {

}