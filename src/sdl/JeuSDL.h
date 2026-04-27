#ifndef JEUSDL_H
#define JEUSDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Jeu.h"
#include "Image.h"

/**
 * @file JeuSDL.h
 * Gère l’affichage et les interactions avec SDL.
 */

/**
 * @class JeuSDL
 * Permet de faire le lien entre la logique du jeu et l’affichage graphique.
 */
class JeuSDL {
private:
    Jeu jeu;                 /**< Instance du jeu */

    SDL_Window* fenetre;     /**< Fenêtre SDL */
    SDL_Renderer* rendu;     /**< Renderer SDL */
    TTF_Font* police;        /**< Police utilisée */

    Image im_auraMorts;
    Image im_joueur;
    Image im_degats;
    Image im_cadence;
    Image im_taille;
    Image im_vitesseProjectile;
    Image im_vitesseJoueur;
    Image im_multitir;
    Image im_auraMort;
    Image im_tirPerforant;
    Image im_auraJoueur;
    Image im_foudre;
    Image im_fondNiv1;
    Image im_zoneSoin;
    Image im_zombie;
    Image im_archer;
    Image im_healer;
    Image im_sorcier;
    Image im_slime;
    Image im_boss;

public:
    /**
     * Initialise SDL et les ressources.
     */
    JeuSDL();

    /**
     * Libère les ressources SDL.
     */
    ~JeuSDL();

    /**
     * Affiche le jeu à l’écran.
     */
    void afficher();

    /**
     * Affiche l’écran de choix des améliorations.
     */
    void afficherChoixAmeliorations();

    /**
     * Boucle principale du jeu.
     */
    void boucle();
};

#endif