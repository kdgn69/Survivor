#include "Rectangle.h"
#include <cmath>

bool collisionRectangles(const Rectangle& a, const Rectangle& b) {
    // si un rectangle est complètement à gauche de l'autre, il n'y a pas collision
    if (a.x + a.largeur <= b.x) return false;
    if (b.x + b.largeur <= a.x) return false;

    // même idée pour le haut et le bas
    if (a.y + a.hauteur <= b.y) return false;
    if (b.y + b.hauteur <= a.y) return false;

    return true;
}

bool rectanglesColles(const Rectangle& a, const Rectangle& b) {
    float epsilon = 0.1;

    if (collisionRectangles(a, b)) {
        return true;
    }
    // côté gauche de A contre droite de B
    if (abs((a.x) - (b.x + b.largeur)) < epsilon) {
        if (!(a.y + a.hauteur <= b.y || b.y + b.hauteur <= a.y)) {
            return true;
        }
    }
    // côté droit de A contre gauche de B
    if (abs((a.x + a.largeur) - (b.x)) < epsilon) {
        if (!(a.y + a.hauteur <= b.y || b.y + b.hauteur <= a.y)) {
            return true;
        }
    }
    // haut de A contre bas de B
    if (abs((a.y) - (b.y + b.hauteur)) < epsilon) {
        if (!(a.x + a.largeur <= b.x || b.x + b.largeur <= a.x)) {
            return true;
        }
    }
    // bas de A contre haut de B
    if (abs((a.y + a.hauteur) - (b.y)) < epsilon) {
        if (!(a.x + a.largeur <= b.x || b.x + b.largeur <= a.x)) {
            return true;
        }
    }
    return false;
}