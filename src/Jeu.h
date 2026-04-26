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
    vector<Projectile> projectilesEnnemis;
    vector<Amelioration> choixAmeliorations;
    vector<Aura> auras;

    bool enChoixAmelioration;

    //compteur pour les ameliorations
    int niveauMultitir;
    int niveauAuraMorts;
    int niveauAuraJoueur;
    int niveauFoudre;
    bool tirPerforantActif;

public:
    Jeu();

    void initialiser();
    void avancerTour();
    void genererVagueActuelle();
    void genererEnnemis(int nombre, TypeEnnemi type, int pv, float vitesse, int largeur, int hauteur, float distanceMinJoueur, int degats);

    void deplacerJoueur(char direction);
    void deplacerEnnemisVersJoueur();
    void tirer(float angleDegres);
    void faireTirerEnnemis(float maintenant);
    Projectile creerProjectileDepuisEnnemi(const Ennemi& ennemi, const Position& cible) const;

    void deplacerProjectilesAllies();
    void deplacerProjectilesEnnemis();
    void gererCollisionsProjectilesAllieSurLesEnnemis();
    void gererCollisionsProjectilesEnnemisSurJoueur();
    void ajouterProjectileEnnemi(const Projectile& p);

    void genererChoixAmeliorations();
    void appliquerAmeliorationChoisie(int index);
    void lancerVagueSuivante();

    void gererMortsEnnemis();
    void mettreAJourAuras();
    void mettreAJourEtatAuraJoueur();
    void appliquerDegatsDesAuras();

    Joueur& getJoueur();
    const Joueur& getJoueur() const;
    const vector<Ennemi>& getEnnemis() const;
    const vector<Projectile>& getProjectilesAllies() const;
    const vector<Projectile>& getProjectilesEnnemis() const;
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