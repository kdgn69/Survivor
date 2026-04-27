#include "Vague.h"

using namespace std;

Vague::Vague() {
    niveau = 1;
    numero = 1;
}

void Vague::passerSuivante() {
    numero++;

    if (numero > 6) {
        numero = 1;
        niveau++;
    }
}

int Vague::getNumero() const {
    return numero;
}

int Vague::getNiveau() const {
    return niveau;
}

int Vague::getNombreEnnemis() const {
    return 5;
}