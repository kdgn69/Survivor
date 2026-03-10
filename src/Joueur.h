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
    //il faudra un tableau darme que stocke  le joueur

public:
    Joueur();
    void seDeplacerVersEnnemi();
    void tirer();    

};
#endif