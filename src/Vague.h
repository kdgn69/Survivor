#ifndef VAGUE_H
#define VAGUE_H

#include "Ennemi.h"
#include <vector>

using namespace std;

class Vague {
private:
    int numero;
    int nombreEnnemis;
    vector<Ennemi>ennemis;

public:
    void genererEnnemis ();
};

#endif