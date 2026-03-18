#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Jeu.h"

using namespace std;

int main() {
    SDL_SetMainReady();
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Erreur SDL : " << SDL_GetError() << endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cerr << "Erreur SDL_image : " << IMG_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    const int LARGEUR_FENETRE = 1280;
    const int HAUTEUR_FENETRE = 720;

    SDL_Window* fenetre = SDL_CreateWindow(
        "Survivor",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        LARGEUR_FENETRE,
        HAUTEUR_FENETRE,
        0
    );

    if (fenetre == nullptr) {
        cerr << "Erreur fenetre : " << SDL_GetError() << endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    if (rendu == nullptr) {
        cerr << "Erreur renderer : " << SDL_GetError() << endl;
        SDL_DestroyWindow(fenetre);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    Jeu jeu;
    jeu.initialiser();

    bool quitter = false;
    SDL_Event event;

    while (!quitter) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitter = true;
            }
        }

        const Uint8* etatClavier = SDL_GetKeyboardState(nullptr);
        jeu.update(etatClavier);

        string titre = "Survivor - Niveau " + to_string(jeu.getNiveauActuel()) +
                       " - Vague " + to_string(jeu.getNumeroVague());
        SDL_SetWindowTitle(fenetre, titre.c_str());

        jeu.render(rendu);
        SDL_RenderPresent(rendu);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    IMG_Quit();
    SDL_Quit();

    return 0;
}