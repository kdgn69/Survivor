#ifndef RECTANGLE_H
#define RECTANGLE_H

struct Rectangle {
    float x;
    float y;
    float largeur;
    float hauteur;
};
bool collisionRectangles(const Rectangle& a, const Rectangle& b);
bool rectanglesColles(const Rectangle& a, const Rectangle& b);

#endif