#include "Projectile.h"

using namespace std;

Projectile::Projectile() {
    pos.x = 0;
    pos.y = 0;
    direction.dx = 0;
    direction.dy = 0;
    actif = false;
}

void Projectile::initialiser(float x, float y, int dx, int dy) {
    pos.x = x;
    pos.y = y;
    direction.dx = dx;
    direction.dy = dy;
    actif = true;
}

void Projectile::avancer() {
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