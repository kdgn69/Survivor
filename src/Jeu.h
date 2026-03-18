#ifndef JEU_H
#define JEU_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "Vague.h"
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
    vector<Projectile> projectileEnnemi;
    vector<Projectile> projectileAllie;

public:
    Jeu();

    void initialiser();
    void update(const Uint8* etatClavier);
    void genererEnnemisDebut();
    void render(SDL_Renderer* rendu) const;

    Joueur& getJoueur();
    const vector<Ennemi>& getEnnemis() const;
    int getNiveauActuel() const;
    int getNumeroVague() const;
    int getLargeurCarte() const;
    int getHauteurCarte() const;
};

#endif