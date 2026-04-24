#ifndef JOUEUR_H
#define JOUEUR_H

#include "Position.h"
#include "Arme.h"
#include "Rectangle.h"
#include <vector>

using namespace std;

class Ennemi;

class Joueur {
private:
    Position pos;
    int vie;
    float vitesse;
    int largeur;
    int hauteur;
    Arme arme;
    bool tirPerforant;

public:
    Joueur();

    void setPosition(float x, float y);

    void deplacerAvecDirection(char direction, const vector<Ennemi>& ennemis);
    void augmenterVitesse(float bonus);
    void prendreDegats(int degats);

    Position getPosition() const;
    int getVie() const;
    int getLargeur() const;
    int getHauteur() const;

    Arme& getArme();
    const Arme& getArme() const;

    Rectangle getRectangle() const;
    Rectangle getRectangleAvecPosition(float x, float y) const;

    bool aTirPerforant() const;
    void activerTirPerforant();
};

#endif