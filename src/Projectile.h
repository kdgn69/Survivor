#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Position.h"
#include "Direction.h"

using namespace std;

class Projectile {
private:
    Position pos;
    Direction direction;
    bool actif;

public:
    Projectile();

    void initialiser(float x, float y, int dx, int dy);
    void avancer();

    Position getPosition() const;
    int getDirectionX() const;
    int getDirectionY() const;
    bool estActif() const;

    void desactiver();
};

#endif