#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Position.h"
#include "Direction.h"
#include "Rectangle.h"

using namespace std;

class Projectile {
private:
    Position pos;
    Direction direction;
    bool actif;

public:
    Projectile();

    void initialiser(float x, float y, float dx, float dy);
    void avancer();

    Position getPosition() const;
    Rectangle getRectangle() const;
    bool estActif() const;

    void desactiver();
};

#endif