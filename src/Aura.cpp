#include "Aura.h"

Aura::Aura(float x, float y, float r, int d, float dur, float inter, TypeAura t) {
    pos.x = x;
    pos.y = y;
    rayon = r;
    degats = d;
    duree = dur;
    intervalle = inter;
    type = t;

    tempsDepuisCreation = 0;
    tempsDepuisDernierDegat = 0;
}

//deltaTemps = temps écoulé depuis la dernière frame
void Aura::mettreAJour(float deltaTemps) {
    // on augmente le temps total depuis la création de l’aura
    tempsDepuisCreation += deltaTemps;
    // on augmente le temps depuis les derniers dégâts
    tempsDepuisDernierDegat += deltaTemps;
}

bool Aura::estExpiree() const {
    // si le temps de vie dépasse la durée max l’aura disparaît
    return tempsDepuisCreation >= duree;
}

bool Aura::peutInfligerDegats() {
    // si assez de temps s'est écoulé depuis les derniers degats
    if (tempsDepuisDernierDegat >= intervalle) {
        // on remet le compteur à 0 pour attendre la prochaine atq
        tempsDepuisDernierDegat = 0;
        // on autorise les degats
        return true;
    }
    return false;
}

Position Aura::getPosition() const {
    return pos;
}

float Aura::getRayon() const {
    return rayon;
}

int Aura::getDegats() const {
    return degats;
}

TypeAura Aura::getType() const {
    return type;
}

void Aura::setPosition(float x, float y) {
    pos.x = x;
    pos.y = y;
}

void Aura::setRayon(float r) {
    rayon = r;
}

void Aura::setDegats(int d) {
    degats = d;
}

void Aura::setIntervalle(float i) {
    intervalle = i;
}