/**
 * @file Ennemi.h
 * Gère les ennemis du jeu.
 */

/**
 * @enum TypeEnnemi
 * Définit les différents types d’ennemis.
 */
enum TypeEnnemi {
    ZOMBIE,
    ARCHER,
    HEALER,
    SORCIER,
    SLIME,
    BOSS
};

/**
 * @class Ennemi
 * Représente un ennemi avec ses caractéristiques et son comportement.
 */
class Ennemi {
private:
    Position pos;          /**< Position de l’ennemi */
    int vie;               /**< Points de vie */
    float vitesse;         /**< Vitesse de déplacement */
    int largeur;           /**< Largeur */
    int hauteur;           /**< Hauteur */
    TypeEnnemi type;       /**< Type d’ennemi */
    float dernierTir;      /**< Temps du dernier tir */
    Arme arme;             /**< Arme de l’ennemi */
    int degats;            /**< Dégâts infligés */
    float rayonEffet;      /**< Rayon d’effet (soin ou zone) */
    bool peutSeDiviser;    /**< Indique si l’ennemi peut se diviser */

public:
    /**
     * Crée un ennemi avec ses caractéristiques.
     */
    Ennemi(float x, float y, TypeEnnemi t, int pv, float vit, int larg, int haut, int deg);

    /**
     * Déplace l’ennemi vers le joueur.
     */
    void seDeplacerVersJoueur(const Position& posJoueur, int largeurJoueur, int hauteurJoueur);

    /**
     * Inflige des dégâts à l’ennemi.
     */
    void prendreDegats(int degats);

    /**
     * Indique si l’ennemi est mort.
     */
    bool estMort() const;

    /**
     * Retourne la position.
     */
    Position getPosition() const;

    /**
     * Dimensions.
     */
    int getLargeur() const;
    int getHauteur() const;

    /**
     * Retourne le type.
     */
    TypeEnnemi getType() const;

    /**
     * Temps du dernier tir.
     */
    float getDernierTir() const;

    /**
     * Rectangle pour les collisions.
     */
    Rectangle getRectangle() const;
    Rectangle getRectangleAvecPosition(float x, float y) const;

    /**
     * Retourne les dégâts.
     */
    int getDegats() const;

    /**
     * Rayon d’effet.
     */
    float getRayonEffet() const;

    /**
     * Indique si l’ennemi peut se diviser.
     */
    bool getPeutSeDiviser() const;

    /**
     * Accès à l’arme.
     */
    Arme& getArme();
    const Arme& getArme() const;

    /**
     * Modifie le temps du dernier tir.
     */
    void setDernierTir(float t);

    /**
     * Active ou désactive la division.
     */
    void setPeutSeDiviser(bool val);
};