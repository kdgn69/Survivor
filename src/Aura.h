#ifndef AURA_H
#define AURA_H

#include "Position.h"

enum TypeAura {
    AURA_MORT,
    AURA_JOUEUR
};

class Aura {
private:
    Position pos;
    float rayon;
    int degats;
    float duree;
    float intervalle;
    float tempsDepuisCreation;
    float tempsDepuisDernierDegat;
    TypeAura type;

public:
    Aura(float x, float y, float r, int d, float dur, float inter, TypeAura t);

    void mettreAJour(float deltaTemps);

    bool estExpiree() const;
    bool peutInfligerDegats();

    Position getPosition() const;
    float getRayon() const;
    int getDegats() const;
    TypeAura getType() const;

    void setPosition(float x, float y);
    void setRayon(float r);
    void setDegats(int d);
    void setIntervalle(float i);
};

#endif