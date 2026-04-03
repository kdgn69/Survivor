#ifndef JEUCONSOLE_H
#define JEUCONSOLE_H

#include "../Jeu.h"

using namespace std;

class JeuConsole {
private:
    Jeu jeu;

public:
    JeuConsole();

    void afficher() const;
    void boucle();
};

#endif