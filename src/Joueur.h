#ifndef JOUEUR_H
#define JOUEUR_H

#include "Position.h"
#include "Arme.h"

class Joueur {
private:
    Position pos;
    int vie;
    float vitesse;
    Arme arme;

public:
    void SeDeplacer();
    void tirer();    

};
#endif