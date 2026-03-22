#ifndef RECTANGLE_H
#define RECTANGLE_H

struct Rectangle {
    int x;
    int y;
    int largeur;
    int hauteur;
};

bool collisionRectangles(const Rectangle& a, const Rectangle& b);

#endif