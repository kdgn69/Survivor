#include "Rectangle.h"
#include <iostream>

bool collisionRectangles(const Rectangle& a, const Rectangle& b) {
    if (a.x + a.largeur <= b.x) return false;
    if (b.x + b.largeur <= a.x) return false;
    if (a.y + a.hauteur <= b.y) return false;
    if (b.y + b.hauteur <= a.y) return false;
    return true;
}