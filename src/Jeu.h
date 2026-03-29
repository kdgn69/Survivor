#ifndef JEU_H
#define JEU_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
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

    // Version console
    void updateConsole(char commande);
    void updateTirConsole(float angleDegres);

    // Version SDL
    void updateSDL(const Uint8* etatClavier);
    void renderSDL(SDL_Renderer* rendu) const;

    void genererEnnemisDebut();

    void tirerConsole(float angleDegres);
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