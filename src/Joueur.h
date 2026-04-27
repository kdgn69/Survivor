/**
 * @file Joueur.h
 * Gère le comportement et les caractéristiques du joueur.
 */

/**
 * @class Joueur
 * Représente le joueur avec ses déplacements, sa vie et son arme.
 */
class Joueur {
private:
    Position pos;       /**< Position du joueur */
    int vie;            /**< Points de vie */
    float vitesse;      /**< Vitesse de déplacement */
    int largeur;        /**< Largeur du joueur */
    int hauteur;        /**< Hauteur du joueur */
    Arme arme;          /**< Arme utilisée */
    bool tirPerforant;  /**< Indique si les tirs traversent les ennemis */
    float dernierTir;   /**< Temps du dernier tir */

public:
    /**
     * Initialise le joueur avec ses valeurs de base.
     */
    Joueur();

    /**
     * Définit la position du joueur.
     */
    void setPosition(float x, float y);

    /**
     * Déplace le joueur en fonction d’une direction.
     * Prend en compte les collisions avec les ennemis.
     */
    void deplacerAvecDirection(char direction, const vector<Ennemi>& ennemis);

    /**
     * Augmente la vitesse du joueur.
     */
    void augmenterVitesse(float bonus);

    /**
     * Inflige des dégâts au joueur.
     */
    void prendreDegats(int degats);

    /**
     * Retourne la position du joueur.
     */
    Position getPosition() const;

    /**
     * Retourne les points de vie.
     */
    int getVie() const;

    /**
     * Retourne la largeur.
     */
    int getLargeur() const;

    /**
     * Retourne la hauteur.
     */
    int getHauteur() const;

    /**
     * Accès à l’arme (modifiable).
     */
    Arme& getArme();

    /**
     * Accès à l’arme (lecture seule).
     */
    const Arme& getArme() const;

    /**
     * Retourne le rectangle pour les collisions.
     */
    Rectangle getRectangle() const;

    /**
     * Retourne un rectangle à une position donnée.
     */
    Rectangle getRectangleAvecPosition(float x, float y) const;

    /**
     * Indique si le tir est perforant.
     */
    bool aTirPerforant() const;

    /**
     * Active le tir perforant.
     */
    void activerTirPerforant();

    /**
     * Retourne le temps du dernier tir.
     */
    float getDernierTir() const;

    /**
     * Met à jour le temps du dernier tir.
     */
    void setDernierTir(float t);
};