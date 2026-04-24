#ifndef ENNEMI_H
#define ENNEMI_H

#include "Position.h"
#include "Rectangle.h"
#include <string>

using namespace std;

enum TypeEnnemi {
    ZOMBIE,
    ARCHER,
    HEALER,
    SORCIERE,
    SLIME
};

class Ennemi {
private:
    Position pos;
    int vie;
    float vitesse;
    int largeur;
    int hauteur;
    TypeEnnemi type;

public:
    Ennemi(float x, float y, TypeEnnemi t, int pv, float vit, int larg, int haut);
    
    void seDeplacerVersJoueur(const Position& posJoueur, int largeurJoueur, int hauteurJoueur);
    void prendreDegats(int degats);
    bool estMort() const;

    Position getPosition() const;
    int getLargeur() const;
    int getHauteur() const;
    TypeEnnemi getType() const;

    Rectangle getRectangle() const;
    Rectangle getRectangleAvecPosition(float x, float y) const;
};

#endif