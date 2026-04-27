#include "Joueur.h"
#include "Ennemi.h"
#include <iostream>

using namespace std;

Joueur::Joueur() {
    vie = 2000000000;
    vitesse = 8;
    largeur = 125;
    hauteur = 125;
    tirPerforant = false;
    dernierTir = 0;

    pos.x = 0;
    pos.y = 0;
}

void Joueur::setPosition(float x, float y) {
    pos.x = x;
    pos.y = y;
}

void Joueur::deplacerAvecDirection(char direction, const vector<Ennemi>& ennemis) {
    float nouveauX = pos.x;
    float nouveauY = pos.y;

    if (direction == 'z') nouveauY -= vitesse;
    if (direction == 's') nouveauY += vitesse;
    if (direction == 'q') nouveauX -= vitesse;
    if (direction == 'd') nouveauX += vitesse;

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

void Joueur::augmenterVitesse(float bonus) {
    vitesse += bonus;
}

void Joueur::prendreDegats(int degats) {
    vie -= degats;
    if (vie < 0) vie = 0;
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

Arme& Joueur::getArme() {
    return arme;
}

const Arme& Joueur::getArme() const {
    return arme;
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

bool Joueur::aTirPerforant() const {
    return tirPerforant;
}

void Joueur::activerTirPerforant() {
    tirPerforant = true;
}

float Joueur::getDernierTir() const {
    return dernierTir;
}

void Joueur::setDernierTir(float t) {
    dernierTir = t;
}