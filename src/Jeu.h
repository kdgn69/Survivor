#ifndef JEU_H
#define JEU_H

#include <vector>
#include "Vague.h"
#include "Joueur.h"
#include "Projectile.h"

using namespace std;

class Jeu  {
private:
    int score;
    Vague vagueActuelle;
    Joueur joueur;
    vector<Projectile>projectileEnnemi;
    vector<Projectile>projectileAllie;

public:
    void update();
    void genererVague();
};

#endif