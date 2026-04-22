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
    bool perforant;
    int degats;
    float largeur;
    float hauteur;

public:
    Projectile();

    Projectile(float x, float y, float dx, float dy, int deg, float larg, float taille);
    void avancer();

    Position getPosition() const;
    Rectangle getRectangle() const;
    bool estActif() const;
    bool estPerforant() const;
    int getDegats() const;
    float getLargeur() const;
    float getHauteur() const;

    void setPerforant(bool val);

    void desactiver();
};

#endif