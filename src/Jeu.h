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

/**
 * @file Jeu.h
 * Contient toute la logique principale du jeu.
 */

/**
 * @class Jeu
 * Gère l’ensemble du déroulement du jeu :
 * joueur, ennemis, projectiles, vagues et améliorations.
 */
class Jeu {
private:
    Vague vague;                         /**< Gestion des vagues et niveaux */
    int largeurCarte;                    /**< Largeur de la carte */
    int hauteurCarte;                    /**< Hauteur de la carte */

    Joueur joueur;                      /**< Joueur */
    vector<Ennemi> ennemis;             /**< Liste des ennemis */
    vector<Projectile> projectilesAllies;   /**< Projectiles du joueur */
    vector<Projectile> projectilesEnnemis;  /**< Projectiles ennemis */
    vector<Amelioration> choixAmeliorations;/**< Choix d'améliorations */
    vector<Aura> auras;                 /**< Auras actives */

    bool enChoixAmelioration;          /**< Indique si le joueur choisit une amélioration */

    int niveauMultitir;               /**< Niveau de multitir */
    int niveauAuraMorts;              /**< Niveau aura des ennemis morts */
    int niveauAuraJoueur;             /**< Niveau aura autour du joueur */
    int niveauFoudre;                 /**< Niveau de la foudre */

    bool jeuTermine;                  /**< Indique si la partie est terminée */
    bool victoire;                    /**< Indique si le joueur a gagné */

public:
    /**
     * Initialise les variables du jeu.
     */
    Jeu();

    /**
     * Initialise la partie (position joueur, première vague).
     */
    void initialiser();

    /**
     * Met à jour le jeu à chaque tour.
     */
    void avancerTour();

    /**
     * Génère la vague actuelle d’ennemis.
     */
    void genererVagueActuelle();

    /**
     * Génère des ennemis avec des caractéristiques données.
     */
    void genererEnnemis(int nombre, TypeEnnemi type, int pv, float vitesse, int largeur, int hauteur, float distanceMinJoueur, int degats);

    /**
     * Déplace le joueur.
     */
    void deplacerJoueur(char direction);

    /**
     * Fait se déplacer les ennemis vers le joueur.
     */
    void deplacerEnnemisVersJoueur();

    /**
     * Fait tirer le joueur.
     */
    void tirer(float angleDegres);

    /**
     * Fait tirer les ennemis.
     */
    void faireTirerEnnemis(float maintenant);

    /**
     * Crée des projectiles à partir d’un ennemi.
     */
    vector<Projectile> creerProjectilesDepuisEnnemi(const Ennemi& ennemi, const Position& cible) const;

    /**
     * Déplace les projectiles du joueur.
     */
    void deplacerProjectilesAllies();

    /**
     * Déplace les projectiles ennemis.
     */
    void deplacerProjectilesEnnemis();

    /**
     * Gère les collisions des projectiles du joueur avec les ennemis.
     */
    void gererCollisionsProjectilesAllieSurLesEnnemis();

    /**
     * Gère les collisions des projectiles ennemis avec le joueur.
     */
    void gererCollisionsProjectilesEnnemisSurJoueur();

    /**
     * Ajoute un projectile ennemi.
     */
    void ajouterProjectileEnnemi(const Projectile& p);

    /**
     * Génère les choix d’améliorations.
     */
    void genererChoixAmeliorations();

    /**
     * Applique l’amélioration choisie.
     */
    void appliquerAmeliorationChoisie(int index);

    /**
     * Lance la vague suivante.
     */
    void lancerVagueSuivante();

    /**
     * Supprime les ennemis morts et applique les effets associés.
     */
    void gererMortsEnnemis();

    /**
     * Met à jour les auras.
     */
    void mettreAJourAuras();

    /**
     * Met à jour l’aura du joueur.
     */
    void mettreAJourEtatAuraJoueur();

    /**
     * Applique les dégâts des auras.
     */
    void appliquerDegatsDesAuras();

    /**
     * Soigne les ennemis dans les zones de soin.
     */
    void soignerEnnemis();

    /**
     * Accès au joueur.
     */
    Joueur& getJoueur();

    const Joueur& getJoueur() const;

    /**
     * Accès aux ennemis.
     */
    const vector<Ennemi>& getEnnemis() const;

    /**
     * Accès aux projectiles du joueur.
     */
    const vector<Projectile>& getProjectilesAllies() const;

    /**
     * Accès aux projectiles ennemis.
     */
    const vector<Projectile>& getProjectilesEnnemis() const;

    /**
     * Accès aux choix d’améliorations.
     */
    const vector<Amelioration>& getChoixAmeliorations() const;

    /**
     * Accès aux auras.
     */
    const vector<Aura>& getAuras() const;

    /**
     * Indique si on est en phase de choix d’amélioration.
     */
    bool estEnChoixAmelioration() const;

    /**
     * Retourne le niveau actuel.
     */
    int getNiveauActuel() const;

    /**
     * Retourne le numéro de la vague.
     */
    int getNumeroVague() const;

    /**
     * Dimensions de la carte.
     */
    int getLargeurCarte() const;
    int getHauteurCarte() const;

    /**
     * Niveau de l’aura du joueur.
     */
    int getNiveauAuraJoueur() const;

    /**
     * Nombre d’ennemis restants.
     */
    int getNombreEnnemisRestants() const;

    /**
     * Indique si la partie est terminée.
     */
    bool estTermine() const;

    /**
     * Indique si le joueur a gagné.
     */
    bool estVictoire() const;
};

#endif