#ifndef ARME_H
#define ARME_H

class Arme {
private:
    int degats;
    float cadence; // tirs par seconde
    float largeurProjectile;
    float hauteurProjectile;
    float vitesseProjectile;

public:
    Arme() {
        degats = 10;
        cadence = 2;
        largeurProjectile = 5;
        hauteurProjectile = 5;
        vitesseProjectile = 3;
    }

    int getDegats() const {
        return degats;
    }

    float getCadence() const {
        return cadence;
    }

    float getLargeurProjectile() const {
        return largeurProjectile;
    }

    float getHauteurProjectile() const {
        return hauteurProjectile;
    }

    float getVitesseProjectile() const {
        return vitesseProjectile;
    }

    void augmenterDegats(int bonus) {
        degats += bonus;
    }

    void augmenterCadence(float bonus) {
        cadence += bonus;
    }

    void augmenterLargeurProjectile(float bonus) {
        largeurProjectile += bonus;
    }

    void augmenterHauteurProjectile(float bonus) {
        hauteurProjectile += bonus;
    }

    unsigned int getIntervalleTirMs() const {
        if (cadence <= 0) {
            return 1000;
        }

        unsigned int intervalle = (unsigned int)(1000 / cadence);

        if (intervalle < 1) {
            intervalle = 1;
        }

        return intervalle;
    }
};

#endif