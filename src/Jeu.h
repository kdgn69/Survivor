#ifndef JEU_H
#define JEU_H

#include <vector>
#include <string>
#include "Joueur.h"
#include "Projectile.h"
#include "Ennemi.h"
#include "Vague.h"
#include "Amelioration.h"
#include "Aura.h"

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
    vector<Aura> auras;

    bool enChoixAmelioration;

    //compteur pour l'amelioration multi-tir
    int niveauMultitir;
    int niveauAura;
    int niveauAuraJoueur;
    bool tirPerforantActif;

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

    void mettreAJourAuras(float deltaTemps);
    void appliquerDegatsAuras();
    void appliquerAuraJoueur(float deltaTemps);

    Joueur& getJoueur();
    const Joueur& getJoueur() const;
    const vector<Ennemi>& getEnnemis() const;
    const vector<Projectile>& getProjectilesAllies() const;
    const vector<Amelioration>& getChoixAmeliorations() const;
    const vector<Aura>& getAuras() const;

    bool estEnChoixAmelioration() const;

    int getNiveauActuel() const;
    int getNumeroVague() const;
    int getLargeurCarte() const;
    int getHauteurCarte() const;
    int getNiveauAuraJoueur() const;
    int getNombreEnnemisRestants() const;
};

#endif