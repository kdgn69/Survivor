#ifndef JEU_H
#define JEU_H

#include <vector>
#include <string>
#include "Joueur.h"
#include "Projectile.h"
#include "Ennemi.h"

using namespace std;

class Jeu {
private:
    int niveauActuel;
    int numeroVague;
    int largeurCarte;
    int hauteurCarte;

    Joueur joueur;
    vector<Ennemi> ennemis;
    vector<Projectile> projectilesAllies;

public:
    Jeu();

    void initialiser();
    void genererEnnemisDebut();

    void deplacerJoueur(char direction);
    void tirerAngle(float angleDegres);
    void avancerTour();

    void deplacerProjectilesAllies();
    void gererCollisionsProjectilesEnnemis();

    Joueur& getJoueur();
    const Joueur& getJoueur() const;
    const vector<Ennemi>& getEnnemis() const;
    const vector<Projectile>& getProjectilesAllies() const;

    int getNiveauActuel() const;
    int getNumeroVague() const;
    int getLargeurCarte() const;
    int getHauteurCarte() const;
};

#endif 