#include "Projectile.h"
#include "Rectangle.h"

using namespace std;

Projectile::Projectile(float x, float y, float dx, float dy, int deg, float larg, float taille) {
    pos.x = x;
    pos.y = y;
    direction.dx = dx;
    direction.dy = dy;
    actif = true;
    perforant = false;
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

bool Projectile::estPerforant() const {
    return perforant;
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

void Projectile::setPerforant(bool val) {
    perforant = val;
}

void Projectile::desactiver() {
    actif = false;
}
