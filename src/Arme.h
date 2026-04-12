#ifndef ARME_H
#define ARME_H

class Arme {
private:
    int degats;
    float cadence; //tirs par secondes
    float largeurProjectile;
    float hauteurProjectile;
    float vitesseProjectile;

public:
    Arme();

    int getDegats() const;
    float getCadence() const;
    float getLargeurProjectile() const;
    float getHauteurProjectile() const;
    float getVitesseProjectile() const;

    void augmenterDegats(int bonus);
    void augmenterCadence(float bonus);
    void augmenterLargeurProjectile(float bonus);
    void augmenterHauteurProjectile(float bonus);

    unsigned int getIntervalleTirMs() const;
};

#endif