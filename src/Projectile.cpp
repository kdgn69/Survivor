#include "Projectile.h"
#include "Rectangle.h"
#include <iostream>

using namespace std;

Projectile::Projectile() {
    pos.x = 0;
    pos.y = 0;
    direction.dx = 0;
    direction.dy = 0;
    actif = false;
    degats = 0;
    largeur = 6;
    hauteur = 6;
}

Projectile::Projectile(float x, float y, float dx, float dy, int deg, float larg, float taille) {
    pos.x = x;
    pos.y = y;
    direction.dx = dx;
    direction.dy = dy;
    actif = true;
    degats = deg;
    largeur = larg;
    hauteur = taille;
}

void Projectile::avancer() {
    // le projectile avance selon sa direction
    if (actif) {
        pos.x += direction.dx;
        pos.y += direction.dy;
    }
}

Position Projectile::getPosition() const {
    return pos;
}

Rectangle Projectile::getRectangle() const {
    Rectangle r;
    r.x = pos.x - largeur / 2;
    r.y = pos.y - hauteur / 2;
    r.largeur = largeur;
    r.hauteur = hauteur;
    return r;
}

bool Projectile::estActif() const {
    return actif;
}

int Projectile::getDegats() const {
    return degats;
}

float Projectile::getLargeur() const {
    return largeur;
}

float Projectile::getHauteur() const {
    return hauteur;
}

void Projectile::desactiver() {
    actif = false;
}
