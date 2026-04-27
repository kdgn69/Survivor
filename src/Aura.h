/**
 * @file Aura.h
 * Gère les zones d’effet infligeant des dégâts.
 */

/**
 * @enum TypeAura
 * Définit les types d’aura.
 */
enum TypeAura {
    AURA_MORT,
    AURA_JOUEUR
};

/**
 * @class Aura
 * Représente une zone qui inflige des dégâts dans un rayon.
 */
class Aura {
private:
    Position pos;                    /**< Position de l’aura */
    float rayon;                     /**< Rayon d’effet */
    int degats;                      /**< Dégâts infligés */
    float duree;                     /**< Durée de vie */
    float intervalle;                /**< Intervalle entre les dégâts */
    float tempsDepuisCreation;       /**< Temps écoulé depuis la création */
    float tempsDepuisDernierDegat;   /**< Temps depuis les derniers dégâts */
    TypeAura type;                   /**< Type d’aura */

public:
    /**
     * Crée une aura avec ses caractéristiques.
     */
    Aura(float x, float y, float r, int d, float dur, float inter, TypeAura t);

    /**
     * Met à jour le temps de l’aura.
     */
    void mettreAJour();

    /**
     * Indique si l’aura est expirée.
     */
    bool estExpiree() const;

    /**
     * Indique si l’aura peut infliger des dégâts.
     */
    bool peutInfligerDegats();

    /**
     * Retourne la position.
     */
    Position getPosition() const;

    /**
     * Retourne le rayon.
     */
    float getRayon() const;

    /**
     * Retourne les dégâts.
     */
    int getDegats() const;

    /**
     * Retourne le type.
     */
    TypeAura getType() const;

    /**
     * Modifie la position.
     */
    void setPosition(float x, float y);

    /**
     * Modifie le rayon.
     */
    void setRayon(float r);

    /**
     * Modifie les dégâts.
     */
    void setDegats(int d);

    /**
     * Modifie l’intervalle.
     */
    void setIntervalle(float i);
};