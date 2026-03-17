#ifndef JOUEUR_H
#define JOUEUR_H

#include "Position.h"
#include "Arme.h"
#include <SDL2/SDL.h>

class Joueur {
private:
    Position pos;
    int vie;
    float vitesse;
    Arme arme;
    //il faudra un tableau darme que stocke le joueur

public:
    Joueur();
    void seDeplacer(const Uint8* etatClavier);
    void tirer();    

};

#endif