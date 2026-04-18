#ifndef AURA_H
#define AURA_H

#include "Position.h"

class Aura {
private:
    Position pos;
    float rayon;
    int degats;
    float duree;
    float intervalle;
    float tempsDepuisCreation;
    float tempsDepuisDernierDegat;

public:
    Aura(float x, float y, float r, int d, float dur, float inter);

    void mettreAJour(float deltaTemps);

    bool estExpiree() const;
    bool peutInfligerDegats();

    Position getPosition() const;
    float getRayon() const;
    int getDegats() const;
};

#endif