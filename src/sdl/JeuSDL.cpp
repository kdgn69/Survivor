#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <iostream>
#include <string>
#include "JeuSDL.h"

using namespace std;

JeuSDL::JeuSDL() : jeu(), fenetre(nullptr), rendu(nullptr), police(nullptr), textureAura(nullptr) {
}

float JeuSDL::calculerAngleJoueurVersSouris(int sourisX, int sourisY) const {
    Position posJoueur = jeu.getJoueur().getPosition();

    float dx = sourisX - posJoueur.x;
    float dy = posJoueur.y - sourisY;

    float angleRadians = atan2(dy, dx);
    float angleDegres = angleRadians * 180 / 3.14159265;

    return angleDegres;
}

//conversion d'un rectangle en sdl pour alléger le code
SDL_FRect JeuSDL::convertirRect(const Rectangle& r) const {
    SDL_FRect sdl;
    sdl.x = r.x;
    sdl.y = r.y;
    sdl.w = r.largeur;
    sdl.h = r.hauteur;
    return sdl;
}

void JeuSDL::afficherTexte(const string& texte, int x, int y) const {
    if (!police) return;

    SDL_Color couleur = {255, 255, 255};

    SDL_Surface* surface = TTF_RenderText_Blended(police, texte.c_str(), couleur);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);

    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopyF(rendu, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
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

    // affichage des auras
    const vector<Aura>& auras = jeu.getAuras();

    for (unsigned int i = 0; i < auras.size(); i++) {
        Position pos = auras[i].getPosition();
        float rayon = auras[i].getRayon();

        SDL_FRect rectAura;
        rectAura.x = pos.x - rayon;
        rectAura.y = pos.y - rayon;
        rectAura.w = rayon * 2;
        rectAura.h = rayon * 2;

        if (textureAura != nullptr) {
            SDL_RenderCopyF(rendu, textureAura, nullptr, &rectAura);
        }
    }

    SDL_FRect rectJoueur = convertirRect(jeu.getJoueur().getRectangle());

    SDL_SetRenderDrawColor(rendu, 50, 100, 255, 255);
    SDL_RenderFillRectF(rendu, &rectJoueur);

    const vector<Ennemi>& ennemis = jeu.getEnnemis();
    for (unsigned int i = 0; i < ennemis.size(); i++) {
        SDL_FRect rectEnnemi = convertirRect(ennemis[i].getRectangle());

        SDL_SetRenderDrawColor(rendu, 120, 50, 50, 255);
        SDL_RenderFillRectF(rendu, &rectEnnemi);
    }

    const vector<Projectile>& projectiles = jeu.getProjectilesAllies();
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        SDL_FRect rectProjectile = convertirRect(projectiles[i].getRectangle());

        SDL_SetRenderDrawColor(rendu, 255, 230, 80, 255);
        SDL_RenderFillRectF(rendu, &rectProjectile);
    }

    // si on est en train de choisir une amélioration
    if (jeu.estEnChoixAmelioration()) {
        afficherChoixAmeliorations();
    }
}

void JeuSDL::afficherChoixAmeliorations() const {
    const vector<Amelioration>& choix = jeu.getChoixAmeliorations();

    // largeur et hauteur d'une carte d'amélioration
    int largeurCarte = 250;
    int hauteurCarte = 350;

    // espace entre les 3 améliorations
    int espace = 50;

    // largeur totale des 3 améliorations + les espaces entre elles
    int totalLargeur = 3 * largeurCarte + 2 * espace;

    // point de départ en X pour centrer tout le bloc au milieu de l'écran
    // en gros on prend la largeur de l'écran et on enlève la largeur totale
    int startX = (jeu.getLargeurCarte() - totalLargeur) / 2;

    // position verticale (on centre les cartes en hauteur)
    int y = (jeu.getHauteurCarte() - hauteurCarte) / 2;


    // boucle pour afficher les améliorations
    for (int i = 0; i < 3; i++) {

        // position X de chaque carte
        // on décale à chaque fois de (largeurCarte + espace)
        int x = startX + i * (largeurCarte + espace);

        // rectangle principal de la carte
        SDL_FRect rect;
        rect.x = x;
        rect.y = y;
        rect.w = largeurCarte;
        rect.h = hauteurCarte;

        // fond carte
        SDL_SetRenderDrawColor(rendu, 60, 60, 60, 255);
        SDL_RenderFillRectF(rendu, &rect);

        // bordure
        SDL_SetRenderDrawColor(rendu, 200, 200, 200, 255);
        SDL_RenderDrawRectF(rendu, &rect);

        string nom = choix[i].nom;

        // on affiche le nom de l'amélioration en haut
        afficherTexte(nom, x + 50, y + 10);

        // IMAGE
        SDL_FRect imageRect;
        imageRect.x = x + 50;
        imageRect.y = y + 40;
        imageRect.w = 150;
        imageRect.h = 100;

        string chemin;

        if (nom == "degats") chemin = "data/degats.png";
        else if (nom == "cadence") chemin = "data/cadence.png";
        else if (nom == "taille") chemin = "data/taille.png";
        else if (nom == "vitesseJoueur") chemin = "data/vitesseJoueur.png";
        else if (nom == "vitesseProjectile") chemin = "data/vitesseProjectile.png";
        else if (nom == "multitir") chemin = "data/multitir.png";
        else if (nom == "auraMort") chemin = "data/auraMort.png";

        SDL_Surface* surface = IMG_Load(chemin.c_str());

        if (surface == nullptr) {
            cout << "Erreur chargement image : " << chemin << " | " << IMG_GetError() << endl;
        } else {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);

            if (texture != nullptr) {
                SDL_RenderCopyF(rendu, texture, nullptr, &imageRect);
                SDL_DestroyTexture(texture);
            }

            SDL_FreeSurface(surface);
        }

        // petite description en fonction du type
        string description;

        if (nom == "degats") {
            description = "Augmente les degats";
        }
        else if (nom == "cadence") {
            description = "Augmente la cadence";
        }
        else if (nom == "taille") {
            description = "Projectiles plus gros";
        }
        else if (nom == "vitesseProjectile") {
        description = "Projectiles plus rapides";
        }
        else if (nom == "vitesseJoueur") {
            description = "Deplacement plus rapide";
        }
        else if (nom == "multitir") {
            description = "Encore plus de tirs !";
        }
        else if (nom == "auraMort") {
        description = "La mort apres la mort";
        }

        // on affiche la description sous l'image
        afficherTexte(description, x + 20, y + 200);
    }
}

void JeuSDL::boucle() {
    SDL_SetMainReady();
    SDL_SetWindowTitle(fenetre, "Survivor");

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Erreur SDL : " << SDL_GetError() << endl;
        return;
    }

    IMG_Init(IMG_INIT_PNG);

    if (TTF_Init() == -1) {
        cerr << "Erreur TTF : " << TTF_GetError() << endl;
        SDL_Quit();
        return;
    }

    police = TTF_OpenFont("data/arial.ttf", 16);
    if (!police) {
        cerr << "Erreur chargement police : " << TTF_GetError() << endl;
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
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return;
    }

    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    if (rendu == nullptr) {
        cerr << "Erreur creation renderer : " << SDL_GetError() << endl;
        SDL_DestroyWindow(fenetre);
        fenetre = nullptr;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return;
    }

    SDL_Surface* surfaceAura = IMG_Load("data/auraZone.png");
    if (surfaceAura == nullptr) {
        cout << "Erreur chargement image : data/auraZone.png | " << IMG_GetError() << endl;
    }
    else {
        textureAura = SDL_CreateTextureFromSurface(rendu, surfaceAura);
        SDL_FreeSurface(surfaceAura);
    }

    jeu.initialiser();

    bool quitter = false;
    SDL_Event event;
    Uint32 dernierTir = 0;

    while (!quitter) {

        while (SDL_PollEvent(&event)) {
            // fermeture de la fenêtre
            if (event.type == SDL_QUIT) {
                quitter = true;
            }

            // si on est en train de choisir une amélioration
            if (jeu.estEnChoixAmelioration()) {

                // on détecte une touche du clavier
                if (event.type == SDL_KEYDOWN) {

                    // 1 = première carte
                    if (event.key.keysym.sym == SDLK_1) {
                        jeu.appliquerAmeliorationChoisie(0);
                        jeu.lancerVagueSuivante();
                    }

                    // 2 = deuxième carte
                    if (event.key.keysym.sym == SDLK_2) {
                        jeu.appliquerAmeliorationChoisie(1);
                        jeu.lancerVagueSuivante();
                    }

                    // 3 = troisième carte
                    if (event.key.keysym.sym == SDLK_3) {
                        jeu.appliquerAmeliorationChoisie(2);
                        jeu.lancerVagueSuivante();
                    }
                }
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
        Uint32 intervalleTir = jeu.getJoueur().getArme().getIntervalleTirMs();

        if (tempsActuel - dernierTir >= intervalleTir) {
            float angle = calculerAngleJoueurVersSouris(sourisX, sourisY);
            jeu.tirer(angle);
            dernierTir = tempsActuel;
        }


        jeu.avancerTour();
        afficher();
        SDL_RenderPresent(rendu);
        SDL_Delay(16);
    }

    if (police != nullptr) {
        TTF_CloseFont(police);
        police = nullptr;
    }

    if (textureAura != nullptr) {
        SDL_DestroyTexture(textureAura);
        textureAura = nullptr;
    }

    SDL_DestroyRenderer(rendu);
    rendu = nullptr;

    SDL_DestroyWindow(fenetre);
    fenetre = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}