#include "Arme.h"

Arme::Arme() {
    degats = 10;
    cadence = 2;
    largeurProjectile = 5;
    hauteurProjectile = 5;
    vitesseProjectile = 3;
}

int Arme::getDegats() const {
    return degats;
}

float Arme::getCadence() const {
    return cadence;
}

float Arme::getLargeurProjectile() const {
    return largeurProjectile;
}

float Arme::getHauteurProjectile() const {
    return hauteurProjectile;
}

float Arme::getVitesseProjectile() const {
    return vitesseProjectile;
}

void Arme::augmenterDegats(int bonus) {
    degats += bonus;
}

void Arme::augmenterCadence(float bonus) {
    cadence += bonus;
}

void Arme::augmenterLargeurProjectile(float bonus) {
    largeurProjectile += bonus;
}

void Arme::augmenterHauteurProjectile(float bonus) {
    hauteurProjectile += bonus;
}

unsigned int Arme::getIntervalleTirMs() const {
    if (cadence <= 0) {
        return 1000;
    }

    unsigned int intervalle = (unsigned int)(1000 / cadence);

    if (intervalle < 1) {
        intervalle = 1;
    }

    return intervalle;
}