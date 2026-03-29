#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "Jeu.h"

using namespace std;

// Ces constantes ne servent qu'à cette interface SDL
const int LARGEUR_FENETRE = 1280;
const int HAUTEUR_FENETRE = 640;

int main() {
    SDL_SetMainReady();

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Erreur SDL : " << SDL_GetError() << endl;
        return 1;
    }

    // Création de la fenêtre
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
        return 1;
    }

    // Création du renderer
    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    if (rendu == nullptr) {
        cerr << "Erreur creation renderer : " << SDL_GetError() << endl;
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    Jeu jeu;
    jeu.initialiser();

    bool quitter = false;
    SDL_Event event;

    while (!quitter) {
        // Gestion des événements de la fenêtre
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitter = true;
            }
        }

        const Uint8* etatClavier = SDL_GetKeyboardState(nullptr);
        jeu.updateSDL(etatClavier);

        string titre = "Survivor - Niveau " + to_string(jeu.getNiveauActuel()) +
                       " - Vague " + to_string(jeu.getNumeroVague());
        SDL_SetWindowTitle(fenetre, titre.c_str());

        jeu.renderSDL(rendu);
        SDL_RenderPresent(rendu);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}