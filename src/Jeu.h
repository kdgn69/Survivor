#ifndef JEU_H
#define JEU_H

#include <vector>
#include <string>
#include "Joueur.h"
#include "Projectile.h"
#include "Ennemi.h"
#include "Vague.h"
#include "Amelioration.h"

using namespace std;

class Jeu {
private:
    Vague vague;
    int largeurCarte;
    int hauteurCarte;

    Joueur joueur;
    vector<Ennemi> ennemis;
    vector<Projectile> projectilesAllies;

    vector<Amelioration> choixAmeliorations;
    bool enChoixAmelioration;

    //compteur pour l'amelioration multi-tir
    int niveauMultitir;

public:
    Jeu();

    void initialiser();
    void avancerTour();
    void genererVagueActuelle();
    void genererEnnemis(int nombre, const string& type, bool attaqueDistance, int pv, float vitesse, int largeur, int hauteur, float distanceMinJoueur);

    void deplacerJoueur(char direction);
    void tirer(float angleDegres);

    void deplacerProjectilesAllies();
    void gererCollisionsProjectilesAllieSurLesEnnemis();

    void genererChoixAmeliorations();
    void appliquerAmeliorationChoisie(int index);
    void lancerVagueSuivante();

    Joueur& getJoueur();
    const Joueur& getJoueur() const;
    const vector<Ennemi>& getEnnemis() const;
    const vector<Projectile>& getProjectilesAllies() const;
    const vector<Amelioration>& getChoixAmeliorations() const;

    bool estEnChoixAmelioration() const;

    int getNiveauActuel() const;
    int getNumeroVague() const;
    int getLargeurCarte() const;
    int getHauteurCarte() const;
};

#endif