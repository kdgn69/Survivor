#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Erreur SDL : " << SDL_GetError() << endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cerr << "Erreur SDL_image : " << IMG_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* fenetre = SDL_CreateWindow(
        "Survivor",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
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

    SDL_Texture* fond = IMG_LoadTexture(rendu, "data/fondNiv1.png");

    if (fond == nullptr) {
        cerr << "Erreur chargement image : " << IMG_GetError() << endl;
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    bool quitter = false;
    SDL_Event event;

    while (!quitter) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitter = true;
            }
        }

        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, fond, nullptr, nullptr);
        SDL_RenderPresent(rendu);
    }

    SDL_DestroyTexture(fond);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    IMG_Quit();
    SDL_Quit();

    return 0;
}