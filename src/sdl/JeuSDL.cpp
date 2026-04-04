#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <string>
#include "JeuSDL.h"

using namespace std;

JeuSDL::JeuSDL() : jeu(), fenetre(nullptr), rendu(nullptr) {
}

float JeuSDL::calculerAngleJoueurVersSouris(int sourisX, int sourisY) const {
    Position posJoueur = jeu.getJoueur().getPosition();

    float dx = sourisX - posJoueur.x;
    float dy = posJoueur.y - sourisY;

    float angleRadians = atan2(dy, dx);
    float angleDegres = angleRadians * 180 / 3.14159265;

    return angleDegres;
}

void JeuSDL::afficher() const {
    if (rendu == nullptr) return;

    SDL_SetRenderDrawColor(rendu, 30, 30, 30, 255);
    SDL_RenderClear(rendu);

    SDL_FRect fondCarte;
    fondCarte.x = 0;
    fondCarte.y = 0;
    fondCarte.w = jeu.getLargeurCarte();
    fondCarte.h = jeu.getHauteurCarte();

    SDL_SetRenderDrawColor(rendu, 70, 120, 70, 255);
    SDL_RenderFillRectF(rendu, &fondCarte);

    SDL_SetRenderDrawColor(rendu, 220, 40, 40, 255);
    SDL_RenderDrawRectF(rendu, &fondCarte);

    Rectangle rectJoueurLogique = jeu.getJoueur().getRectangle();

    SDL_FRect rectJoueur;
    rectJoueur.x = rectJoueurLogique.x;
    rectJoueur.y = rectJoueurLogique.y;
    rectJoueur.w = rectJoueurLogique.largeur;
    rectJoueur.h = rectJoueurLogique.hauteur;

    SDL_SetRenderDrawColor(rendu, 50, 100, 255, 255);
    SDL_RenderFillRectF(rendu, &rectJoueur);

    const vector<Ennemi>& ennemis = jeu.getEnnemis();
    for (unsigned int i = 0; i < ennemis.size(); i++) {
        Rectangle rectEnnemiLogique = ennemis[i].getRectangle();

        SDL_FRect rectEnnemi;
        rectEnnemi.x = rectEnnemiLogique.x;
        rectEnnemi.y = rectEnnemiLogique.y;
        rectEnnemi.w = rectEnnemiLogique.largeur;
        rectEnnemi.h = rectEnnemiLogique.hauteur;

        SDL_SetRenderDrawColor(rendu, 120, 50, 50, 255);
        SDL_RenderFillRectF(rendu, &rectEnnemi);
    }

    const vector<Projectile>& projectiles = jeu.getProjectilesAllies();
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        Rectangle rectProjectileLogique = projectiles[i].getRectangle();

        SDL_FRect rectProjectile;
        rectProjectile.x = rectProjectileLogique.x;
        rectProjectile.y = rectProjectileLogique.y;
        rectProjectile.w = rectProjectileLogique.largeur;
        rectProjectile.h = rectProjectileLogique.hauteur;

        SDL_SetRenderDrawColor(rendu, 255, 230, 80, 255);
        SDL_RenderFillRectF(rendu, &rectProjectile);
    }
}

void JeuSDL::boucle() {
    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Erreur SDL : " << SDL_GetError() << endl;
        return;
    }

    fenetre = SDL_CreateWindow(
        "Survivor SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        jeu.getLargeurCarte(),
        jeu.getHauteurCarte(),
        0
    );

    if (fenetre == nullptr) {
        cerr << "Erreur creation fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        return;
    }

    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    if (rendu == nullptr) {
        cerr << "Erreur creation renderer : " << SDL_GetError() << endl;
        SDL_DestroyWindow(fenetre);
        fenetre = nullptr;
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

        if (etatClavier[SDL_SCANCODE_W]) jeu.deplacerJoueur('z');
        if (etatClavier[SDL_SCANCODE_S]) jeu.deplacerJoueur('s');
        if (etatClavier[SDL_SCANCODE_A]) jeu.deplacerJoueur('q');
        if (etatClavier[SDL_SCANCODE_D]) jeu.deplacerJoueur('d');

        int sourisX = 0;
        int sourisY = 0;
        SDL_GetMouseState(&sourisX, &sourisY);

        Uint32 tempsActuel = SDL_GetTicks();
        if (tempsActuel - dernierTir >= intervalleTir) {
            float angle = calculerAngleJoueurVersSouris(sourisX, sourisY);
            jeu.tirer(angle);
            dernierTir = tempsActuel;
        }

        jeu.avancerTour();

        string titre = "Survivor - Niveau " + to_string(jeu.getNiveauActuel()) +
                       " - Vague " + to_string(jeu.getNumeroVague());
        SDL_SetWindowTitle(fenetre, titre.c_str());

        afficher();
        SDL_RenderPresent(rendu);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(rendu);
    rendu = nullptr;

    SDL_DestroyWindow(fenetre);
    fenetre = nullptr;

    SDL_Quit();
}