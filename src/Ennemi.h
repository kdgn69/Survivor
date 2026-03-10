#ifndef ENNEMI_H
#define ENNEMI_H

#include "Position.h"
using namespace std;

class Ennemi {
private:
    
    Position pos;
    int vie;
    float vitesse;
 
public:

void SeDeplacer () ;
void Attaquer () ;
};



#endif