#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Position.h"

using namespace std;

class Projectile {
public:
    Position pos;
    Position direction;
    float vitesse;
    int degats;

private:
    void avancer();
    void verifierCollision();
};

#endif