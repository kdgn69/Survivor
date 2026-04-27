#include <cmath>
#include "Ennemi.h"

using namespace std;

Ennemi::Ennemi(float x, float y, TypeEnnemi t, int pv, float vit, int larg, int haut, int deg) {
    pos.x = x;
    pos.y = y;
    type = t;
    vie = pv;
    vitesse = vit;
    largeur = larg;
    hauteur = haut;
    dernierTir = 0;
    degats = deg;
    if (t == HEALER) {
        rayonEffet = 150;
    }
    else if (t == BOSS) {
        rayonEffet = 300;
    }
    else {
        rayonEffet = 0;
    }
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

TypeEnnemi Ennemi::getType() const {
    return type;
}

float Ennemi::getDernierTir() const {
    return dernierTir;
}

int Ennemi::getDegats() const {
    return degats;
}

float Ennemi::getRayonEffet() const {
    return rayonEffet;
}

bool Ennemi::getPeutSeDiviser() const {
    return peutSeDiviser;
}

Arme& Ennemi::getArme() {
    return arme;
}

const Arme& Ennemi::getArme() const {
    return arme;
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

void Ennemi::setDernierTir(float t) {
    dernierTir = t;
}

void Ennemi::setPeutSeDiviser(bool val) {
    peutSeDiviser = val;
}