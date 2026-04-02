#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <string>
#include "JeuSDL.h"

using namespace std;

const int LARGEUR_FENETRE = 1920;
const int HAUTEUR_FENETRE = 1080;

// convertir la position de la souris en angle
float calculerAngleDegres(const Jeu& jeu, int sourisX, int sourisY) {
    Position posJoueur = jeu.getJoueur().getPosition();

    float centreJoueurX = posJoueur.x + jeu.getJoueur().getLargeur() / 2;
    float centreJoueurY = posJoueur.y + jeu.getJoueur().getHauteur() / 2;

    float dx = sourisX - centreJoueurX;
    float dy = centreJoueurY - sourisY;

    float angleRadians = atan2(dy, dx);
    float angleDegres = angleRadians * 180 / 3.14159265;

    return angleDegres;
}

void afficherJeuSDL(SDL_Renderer* rendu, const Jeu& jeu) {
    // On vide l'écran
    SDL_SetRenderDrawColor(rendu, 30, 30, 30, 255);
    SDL_RenderClear(rendu);

    // Fond de la carte
    SDL_FRect fondCarte;
    fondCarte.x = 0;
    fondCarte.y = 0;
    fondCarte.w = jeu.getLargeurCarte();
    fondCarte.h = jeu.getHauteurCarte();

    SDL_SetRenderDrawColor(rendu, 70, 120, 70, 255);
    SDL_RenderFillRectF(rendu, &fondCarte);

    // Bordure rouge pour bien voir les limites
    SDL_SetRenderDrawColor(rendu, 220, 40, 40, 255);
    SDL_RenderDrawRectF(rendu, &fondCarte);

    // Joueur
    Position posJoueur = jeu.getJoueur().getPosition();

    SDL_FRect rectJoueur;
    rectJoueur.x = posJoueur.x ;
    rectJoueur.y = posJoueur.y;
    rectJoueur.w = jeu.getJoueur().getLargeur();
    rectJoueur.h = jeu.getJoueur().getHauteur();

    SDL_SetRenderDrawColor(rendu, 50, 100, 255, 255);
    SDL_RenderFillRectF(rendu, &rectJoueur);

    // Ennemis
    const vector<Ennemi>& ennemis = jeu.getEnnemis();
    for (unsigned int i = 0; i < ennemis.size(); i++) {
        Position posEnnemi = ennemis[i].getPosition();

        SDL_FRect rectEnnemi;
        rectEnnemi.x = posEnnemi.x;
        rectEnnemi.y = posEnnemi.y;
        rectEnnemi.w = ennemis[i].getLargeur();
        rectEnnemi.h = ennemis[i].getHauteur();

        SDL_SetRenderDrawColor(rendu, 120, 50, 50, 255);
        SDL_RenderFillRectF(rendu, &rectEnnemi);
    }

    // Projectiles
    const vector<Projectile>& projectiles = jeu.getProjectilesAllies();
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        Position posProjectile = projectiles[i].getPosition();

        SDL_FRect rectProjectile;
        rectProjectile.x = posProjectile.x;
        rectProjectile.y = posProjectile.y;
        rectProjectile.w = projectiles[i].getLargeur();
        rectProjectile.h = projectiles[i].getHauteur();

        SDL_SetRenderDrawColor(rendu, 255, 230, 80, 255);
        SDL_RenderFillRectF(rendu, &rectProjectile);
    }
}

void BoucleSDL(Jeu& jeu) {
    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Erreur SDL : " << SDL_GetError() << endl;
        return;
    }

    SDL_Window* fenetre = SDL_CreateWindow(
        "Survivor SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        LARGEUR_FENETRE,
        HAUTEUR_FENETRE,
        0
    );

    if (fenetre == nullptr) {
        cerr << "Erreur creation fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        return;
    }

    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    if (rendu == nullptr) {
        cerr << "Erreur creation renderer : " << SDL_GetError() << endl;
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return;
    }

    jeu.initialiser();

    bool quitter = false;
    SDL_Event event;

    Uint32 dernierTir = 0;
    Uint32 intervalleTir = 500;

    while (!quitter) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitter = true;
            }
        }

        const Uint8* etatClavier = SDL_GetKeyboardState(nullptr);

        // Déplacements du joueur
        if (etatClavier[SDL_SCANCODE_W]) {
            jeu.deplacerJoueur('z');
        }
        if (etatClavier[SDL_SCANCODE_S]) {
            jeu.deplacerJoueur('s');
        }
        if (etatClavier[SDL_SCANCODE_A]) {
            jeu.deplacerJoueur('q');
        }
        if (etatClavier[SDL_SCANCODE_D]) {
            jeu.deplacerJoueur('d');
        }

        // Tir automatique vers la souris
        int sourisX = 0;
        int sourisY = 0;
        SDL_GetMouseState(&sourisX, &sourisY);

        Uint32 tempsActuel = SDL_GetTicks();
        if (tempsActuel - dernierTir >= intervalleTir) {
            float angle = calculerAngleDegres(jeu, sourisX, sourisY);
            jeu.tirer(angle);
            dernierTir = tempsActuel;
        }

        // On fait avancer le tour
        jeu.avancerTour();

        string titre = "Survivor - Niveau " + to_string(jeu.getNiveauActuel()) +
                       " - Vague " + to_string(jeu.getNumeroVague());
        SDL_SetWindowTitle(fenetre, titre.c_str());

        afficherJeuSDL(rendu, jeu);
        SDL_RenderPresent(rendu);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
} 