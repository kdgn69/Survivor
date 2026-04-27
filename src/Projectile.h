#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Position.h"
#include "Direction.h"
#include "Rectangle.h"

/**
 * @file Projectile.h
 * Gère les projectiles tirés par le joueur ou les ennemis.
 */

/**
 * @class Projectile
 * Représente un projectile avec une position, une direction et des dégâts.
 */
class Projectile {
private:
    Position pos;       /**< Position du projectile */
    Direction direction;/**< Direction du déplacement */
    bool actif;         /**< Indique si le projectile est encore actif */
    bool perforant;     /**< Indique si le projectile traverse les ennemis */
    int degats;         /**< Dégâts infligés */
    float largeur;      /**< Largeur du projectile */
    float hauteur;      /**< Hauteur du projectile */

public:
    /**
     * Crée un projectile à partir d’une position et d’une direction.
     */
    Projectile(float x, float y, float dx, float dy, int deg, float larg, float taille);

    /**
     * Fait avancer le projectile.
     */
    void avancer();

    /**
     * Retourne la position actuelle.
     */
    Position getPosition() const;

    /**
     * Retourne le rectangle utilisé pour les collisions.
     */
    Rectangle getRectangle() const;

    /**
     * Indique si le projectile est actif.
     */
    bool estActif() const;

    /**
     * Indique si le projectile est perforant.
     */
    bool estPerforant() const;

    /**
     * Retourne les dégâts du projectile.
     */
    int getDegats() const;

    /**
     * Retourne la largeur.
     */
    float getLargeur() const;

    /**
     * Retourne la hauteur.
     */
    float getHauteur() const;

    /**
     * Active ou désactive le mode perforant.
     */
    void setPerforant(bool val);

    /**
     * Désactive le projectile.
     */
    void desactiver();
};

#endif