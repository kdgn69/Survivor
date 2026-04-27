#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <iostream>
#include "JeuSDL.h"

using namespace std;

void afficherTexte(SDL_Renderer* rendu, TTF_Font* police, const string& texte, int x, int y) {
    if (rendu == nullptr || police == nullptr) {
        return;
    }

    SDL_Color couleur = {255, 255, 255, 255};

    SDL_Surface* surface = TTF_RenderText_Blended(police, texte.c_str(), couleur);
    if (surface == nullptr) {
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
    if (texture == nullptr) {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopyF(rendu, texture, nullptr, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

float calculerAngleJoueurVersSouris(const Jeu& jeu, int sourisX, int sourisY) {

    float centreX = jeu.getLargeurCarte() / 2;
    float centreY = jeu.getHauteurCarte() / 2;

    Position posJoueur = jeu.getJoueur().getPosition();

    // souris écran vers monde
    float sourisMondeX = posJoueur.x + (sourisX - centreX);
    float sourisMondeY = posJoueur.y + (sourisY - centreY);

    float dx = sourisMondeX - posJoueur.x;
    float dy = posJoueur.y - sourisMondeY;

    float angleRadians = atan2(dy, dx);
    float angleDegres = angleRadians * 180 / 3.14159265;

    return angleDegres;
} 

JeuSDL::JeuSDL() : jeu(), fenetre(nullptr), rendu(nullptr), police(nullptr) {
    cout << "Init SDL..." << endl;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Erreur SDL : " << SDL_GetError() << endl;
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "Erreur SDL_image : " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur TTF : " << TTF_GetError() << endl;
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    fenetre = SDL_CreateWindow(
        "Survivor",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        jeu.getLargeurCarte(),
        jeu.getHauteurCarte(),
        0
    );

    if (fenetre == nullptr) {
        cout << "Erreur creation fenetre : " << SDL_GetError() << endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    if (rendu == nullptr) {
        cout << "Erreur creation renderer : " << SDL_GetError() << endl;
        SDL_DestroyWindow(fenetre);
        fenetre = nullptr;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    police = TTF_OpenFont("data/arial.ttf", 16);
    if (police == nullptr) {
        cout << "Erreur chargement police : " << TTF_GetError() << endl;
    }

    // images du jeu
    im_auraMorts.loadFromFile("data/auraMorts.png", rendu);
    im_joueur.loadFromFile("data/joueur.png", rendu);
    im_auraJoueur.loadFromFile("data/auraJoueur.png", rendu);

    // images des améliorations
    im_degats.loadFromFile("data/degats.png", rendu);
    im_cadence.loadFromFile("data/cadence.png", rendu);
    im_taille.loadFromFile("data/taille.png", rendu);
    im_vitesseProjectile.loadFromFile("data/vitesseProjectile.png", rendu);
    im_vitesseJoueur.loadFromFile("data/vitesseJoueur.png", rendu);
    im_multitir.loadFromFile("data/multitir.png", rendu);
    im_auraMort.loadFromFile("data/auraMort.png", rendu);
    im_tirPerforant.loadFromFile("data/tirPerforant.png", rendu);
    im_foudre.loadFromFile("data/foudre.png", rendu);
    im_fondNiv1.loadFromFile("data/fondNiv1.png", rendu);
    im_zoneSoin.loadFromFile("data/zoneSoin.png", rendu);

    jeu.initialiser();

    cout << "Init OK" << endl;
}

JeuSDL::~JeuSDL() {
    if (police != nullptr) {
        TTF_CloseFont(police);
        police = nullptr;
    }

    if (rendu != nullptr) {
        SDL_DestroyRenderer(rendu);
        rendu = nullptr;
    }

    if (fenetre != nullptr) {
        SDL_DestroyWindow(fenetre);
        fenetre = nullptr;
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void JeuSDL::afficher() {
    if (rendu == nullptr) {
        return;
    }

    //fond
    int tailleTile = 1024;

    // centre écran
    float centreX1 = jeu.getLargeurCarte() / 2;
    float centreY1 = jeu.getHauteurCarte() / 2;

    Position posJoueur1 = jeu.getJoueur().getPosition();

    int offsetX = (int)posJoueur1.x % tailleTile;
    int offsetY = (int)posJoueur1.y % tailleTile;

    // on dessine une grille autour du joueur
    for (int i = -3; i <= 3; i++) {
        for (int j = -3; j <= 3; j++) {

            float x = centreX1 - offsetX + i * tailleTile;
            float y = centreY1 - offsetY + j * tailleTile;

            im_fondNiv1.draw(rendu, x, y, tailleTile, tailleTile);
        }
    }
    // CAMERA
    float centreX = jeu.getLargeurCarte() / 2;
    float centreY = jeu.getHauteurCarte() / 2;

    Position posJoueur = jeu.getJoueur().getPosition();

    const vector<Aura>& auras = jeu.getAuras();

    // on parcourt toutes les auras du jeu (joueur + ennemis morts)
    for (unsigned int i = 0; i < auras.size(); i++) {

        float rayon = auras[i].getRayon();

        // AURA DU JOUEUR
        if (auras[i].getType() == AURA_JOUEUR) {

            // le joueur est toujours affiché au centre de l'écran
            float x = centreX - rayon;
            float y = centreY - rayon;

            im_auraJoueur.draw(rendu, x, y, rayon * 2, rayon * 2);
        }

        // AURAS DES ENNEMIS MORTS
        else if (auras[i].getType() == AURA_MORT) {

            Position pos = auras[i].getPosition();

            // conversion monde vers écran (avec la caméra centrée sur le joueur)
            float x = centreX + (pos.x - posJoueur.x) - rayon;
            float y = centreY + (pos.y - posJoueur.y) - rayon;

            im_auraMorts.draw(rendu, x, y, rayon * 2, rayon * 2);
        }
    }

    //JOUEUR
    Rectangle rectJoueur = jeu.getJoueur().getRectangle();
    float xJ = centreX - rectJoueur.largeur / 2;
    float yJ = centreY - rectJoueur.hauteur / 2;
    im_joueur.draw(rendu, xJ, yJ, rectJoueur.largeur, rectJoueur.hauteur);

    //ENNEMIS
    const vector<Ennemi>& ennemis = jeu.getEnnemis();
    for (unsigned int i = 0; i < ennemis.size(); i++) {
        Rectangle rectEnnemi = ennemis[i].getRectangle();

        SDL_FRect rect;
        rect.x = centreX + (rectEnnemi.x - posJoueur.x);
        rect.y = centreY + (rectEnnemi.y - posJoueur.y);
        rect.w = rectEnnemi.largeur;
        rect.h = rectEnnemi.hauteur;

        //AFFICHAGE ZONE HEALER
        if (ennemis[i].getType() == HEALER) {
            float rayon = ennemis[i].getRayonEffet();
            float centreHealerX = rect.x + rect.w / 2;
            float centreHealerY = rect.y + rect.h / 2;
            im_zoneSoin.draw(rendu, centreHealerX - rayon, centreHealerY-rayon, rayon*2, rayon*2);
        }
        SDL_SetRenderDrawColor(rendu, 120, 50, 50, 255);
        SDL_RenderFillRectF(rendu, &rect);
    }

    //PROJECTILES ALLIES
    const vector<Projectile>& projectiles = jeu.getProjectilesAllies();
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        Rectangle rectProjectile = projectiles[i].getRectangle();

        SDL_FRect rect;
        rect.x = centreX + (rectProjectile.x - posJoueur.x);
        rect.y = centreY + (rectProjectile.y - posJoueur.y);
        rect.w = rectProjectile.largeur;
        rect.h = rectProjectile.hauteur;

        SDL_SetRenderDrawColor(rendu, 255, 230, 80, 255);
        SDL_RenderFillRectF(rendu, &rect);
    }

    //PROJECTILES ENNEMIS
    const vector<Projectile>& projE = jeu.getProjectilesEnnemis();
    for (unsigned int i = 0; i < projE.size(); i++) {
        Rectangle r = projE[i].getRectangle();

        SDL_FRect rect;
        rect.x = centreX + (r.x - posJoueur.x);
        rect.y = centreY + (r.y - posJoueur.y);
        rect.w = r.largeur;
        rect.h = r.hauteur;

        SDL_SetRenderDrawColor(rendu, 255, 50, 50, 255);
        SDL_RenderFillRectF(rendu, &rect);
    }

    // écran d'amélioration
    if (jeu.estEnChoixAmelioration()) {
        afficherChoixAmeliorations();
    }

    // affichage niveau / vague / PV
    string texteNiveau = "Niveau : " + to_string(jeu.getNiveauActuel());
    string texteVague = "Vague : " + to_string(jeu.getNumeroVague());
    string textePV = "PV : " + to_string(jeu.getJoueur().getVie());
    string texteEnnemis = "Il reste : " + to_string(jeu.getNombreEnnemisRestants()) + " ennemis";

    afficherTexte(rendu, police, texteNiveau, 20, 20);
    afficherTexte(rendu, police, texteVague, 20, 50);
    afficherTexte(rendu, police, textePV, 20, 80);
    afficherTexte(rendu, police, texteEnnemis, 20, 110);
} 

void JeuSDL::afficherChoixAmeliorations() {
    const vector<Amelioration>& choix = jeu.getChoixAmeliorations();

    int largeurCarte = 250;
    int hauteurCarte = 350;
    int espace = 50;

    int totalLargeur = 3 * largeurCarte + 2 * espace;
    int startX = (jeu.getLargeurCarte() - totalLargeur) / 2;
    int y = (jeu.getHauteurCarte() - hauteurCarte) / 2;

    for (int i = 0; i < 3; i++) {
        int x = startX + i * (largeurCarte + espace);

        SDL_FRect rect;
        rect.x = x;
        rect.y = y;
        rect.w = largeurCarte;
        rect.h = hauteurCarte;

        // fond de la carte
        SDL_SetRenderDrawColor(rendu, 60, 60, 60, 255);
        SDL_RenderFillRectF(rendu, &rect);

        // bordure
        SDL_SetRenderDrawColor(rendu, 200, 200, 200, 255);
        SDL_RenderDrawRectF(rendu, &rect);

        string nom = choix[i].nom;

        // nom de l'amélioration
        afficherTexte(rendu, police, nom, x + 50, y + 10);

        // image de l'amélioration
        int imgX = x + 50;
        int imgY = y + 40;
        int imgW = 150;
        int imgH = 100;

        if (nom == "degats") im_degats.draw(rendu, imgX, imgY, imgW, imgH);
        else if (nom == "cadence") im_cadence.draw(rendu, imgX, imgY, imgW, imgH);
        else if (nom == "taille") im_taille.draw(rendu, imgX, imgY, imgW, imgH);
        else if (nom == "vitesseProjectile") im_vitesseProjectile.draw(rendu, imgX, imgY, imgW, imgH);
        else if (nom == "vitesseJoueur") im_vitesseJoueur.draw(rendu, imgX, imgY, imgW, imgH);
        else if (nom == "multitir") im_multitir.draw(rendu, imgX, imgY, imgW, imgH);
        else if (nom == "auraMort") im_auraMort.draw(rendu, imgX, imgY, imgW, imgH);
        else if (nom == "perforant") im_tirPerforant.draw(rendu, imgX, imgY, imgW, imgH);
        else if (nom == "foudre") im_foudre.draw(rendu, imgX, imgY, imgW, imgH);
        else if (nom == "auraJoueur") im_auraJoueur.draw(rendu, imgX, imgY, imgW, imgH);
        

        // description
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
        else if (nom == "perforant") {
            description = "Des projectiles perforants";
        }
        else if (nom == "foudre") {
            description = "Degats de zone";
        }
        else if (nom == "auraJoueur") {
            description = "Aura autour du joueur";
        }

        afficherTexte(rendu, police, description, x + 20, y + 200);

        // rappel clavier
        string touche = "Touche " + to_string(i + 1);
        afficherTexte(rendu, police, touche, x + 80, y + 300);
    }
}

void JeuSDL::boucle() {
    bool quitter = false;
    SDL_Event event;

    float dernierTirJoueur = 0;
    float dernierTirEnnemis = 0;
    float dernierDegatsEnnemis = 0;
    float dernierSoinHealer = 0;
    float dernierSpawnSorciere = 0;

    while (!quitter) {

        float tempsActuel = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitter = true;
            }

            // choix d'amélioration
            if (jeu.estEnChoixAmelioration() && event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_1) {
                    jeu.appliquerAmeliorationChoisie(0);
                    jeu.lancerVagueSuivante();
                }
                else if (event.key.keysym.sym == SDLK_2) {
                    jeu.appliquerAmeliorationChoisie(1);
                    jeu.lancerVagueSuivante();
                }
                else if (event.key.keysym.sym == SDLK_3) {
                    jeu.appliquerAmeliorationChoisie(2);
                    jeu.lancerVagueSuivante();
                }
            }
        }
        if (!jeu.estEnChoixAmelioration()) {
            const Uint8* etat = SDL_GetKeyboardState(nullptr);

            if (etat[SDL_SCANCODE_W]) jeu.deplacerJoueur('z');
            if (etat[SDL_SCANCODE_S]) jeu.deplacerJoueur('s');
            if (etat[SDL_SCANCODE_A]) jeu.deplacerJoueur('q');
            if (etat[SDL_SCANCODE_D]) jeu.deplacerJoueur('d');

            int sourisX = 0;
            int sourisY = 0;
            SDL_GetMouseState(&sourisX, &sourisY);

            float angle = calculerAngleJoueurVersSouris(jeu, sourisX, sourisY);

            float intervalleTirJoueur = jeu.getJoueur().getArme().getIntervalleTirMs();
            float intervalleTirEnnemis = 800;
            float intervalleDegatsEnnemis = 1000;
            float intervalleSoinHealer = 1000;
            float intervalleSpawnSorciere = 5000;

            if (tempsActuel - dernierTirJoueur >= intervalleTirJoueur) {
                jeu.tirer(angle);
                dernierTirJoueur = tempsActuel;
            }
            if (tempsActuel - dernierTirEnnemis >= intervalleTirEnnemis) {
                const vector<Ennemi>& ennemis = jeu.getEnnemis();
                Position posJoueur = jeu.getJoueur().getPosition();

                for (unsigned int i = 0; i < ennemis.size(); i++) {
                    if (ennemis[i].getType() != ARCHER && ennemis[i].getType() != SORCIERE) continue;
                    Projectile p = jeu.creerProjectileDepuisEnnemi(ennemis[i], posJoueur);
                    jeu.ajouterProjectileEnnemi(p);
                }
                dernierTirEnnemis = tempsActuel;
            }
            if (tempsActuel - dernierDegatsEnnemis >= intervalleDegatsEnnemis) {
                const vector<Ennemi>& ennemis = jeu.getEnnemis();
                Rectangle rectJoueur = jeu.getJoueur().getRectangle();

                for (unsigned int i = 0; i < ennemis.size(); i++) {
                    Rectangle rectEnnemi = ennemis[i].getRectangle();

                    if (rectanglesColles(rectJoueur, rectEnnemi)) {
                        jeu.getJoueur().prendreDegats(ennemis[i].getDegats());
                    }
                }
                dernierDegatsEnnemis = tempsActuel;
            }
            if (tempsActuel - dernierSoinHealer >= intervalleSoinHealer) {
                jeu.soignerEnnemis();
                dernierSoinHealer = tempsActuel;
            }
            if (tempsActuel - dernierSpawnSorciere >= intervalleSpawnSorciere) {
                const vector<Ennemi>& ennemis = jeu.getEnnemis();

                for (unsigned int i = 0; i < ennemis.size(); i++) {
                    if (ennemis[i].getType() != SORCIERE) continue;
                    
                    for (int k = 0; k < 5; k++) {
                        jeu.genererEnnemis(1, ZOMBIE, 80, 4, 25, 25, 0, 5);
                    }
                }
                dernierSpawnSorciere = tempsActuel;
            }
            jeu.avancerTour();
        }
        afficher();
        SDL_RenderPresent(rendu);

        SDL_Delay(16);
    }
}