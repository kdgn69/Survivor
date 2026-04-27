/**
 * @file Arme.h
 * Gère les caractéristiques d’une arme.
 */

/**
 * @class Arme
 * Contient les statistiques utilisées pour tirer des projectiles.
 */
class Arme {
private:
    int degats;              /**< Dégâts infligés */
    float cadence;           /**< Nombre de tirs par seconde */
    float largeurProjectile; /**< Largeur des projectiles */
    float hauteurProjectile; /**< Hauteur des projectiles */
    float vitesseProjectile; /**< Vitesse des projectiles */

public:
    /**
     * Initialise l’arme avec des valeurs de base.
     */
    Arme();

    /**
     * Retourne les dégâts.
     */
    int getDegats() const;

    /**
     * Retourne la cadence.
     */
    float getCadence() const;

    /**
     * Dimensions des projectiles.
     */
    float getLargeurProjectile() const;
    float getHauteurProjectile() const;

    /**
     * Retourne la vitesse des projectiles.
     */
    float getVitesseProjectile() const;

    /**
     * Modifie les caractéristiques de l’arme.
     */
    void augmenterDegats(int bonus);
    void augmenterCadence(float bonus);
    void augmenterLargeurProjectile(float bonus);
    void augmenterHauteurProjectile(float bonus);
    void augmenterVitesseProjectile(float bonus);

    /**
     * Retourne l’intervalle entre deux tirs en millisecondes.
     */
    unsigned int getIntervalleTirMs() const;
};