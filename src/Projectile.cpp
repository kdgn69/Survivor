#include "Projectile.h"
#include <iostream>

using namespace std;

Projectile::Projectile() {
    pos.x = 0;
    pos.y = 0;
    direction.dx = 0;
    direction.dy = 0;
    actif = false;
}

void Projectile::initialiser(float x, float y, float dx, float dy) {
    pos.x = x;
    pos.y = y;
    direction.dx = dx;
    direction.dy = dy;
    actif = true;
}

void Projectile::avancer() {
    // le projectile avance d'une case dans sa direction
    if (actif) {
        pos.x += direction.dx;
        pos.y += direction.dy;
    }
}

Position Projectile::getPosition() const {
    return pos;
}

bool Projectile::estActif() const {
    return actif;
}

void Projectile::desactiver() {
    actif = false;
}