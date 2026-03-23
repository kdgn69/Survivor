#include "Rectangle.h"
#include <iostream>

bool collisionRectangles(const Rectangle& a, const Rectangle& b) {
    // si un rectangle est complètement à gauche de l'autre, il n'y a pas collision
    if (a.x + a.largeur <= b.x) return false;
    if (b.x + b.largeur <= a.x) return false;

    // même idée pour le haut et le bas
    if (a.y + a.hauteur <= b.y) return false;
    if (b.y + b.hauteur <= a.y) return false;

    return true;
}