#include <iostream>
#include "Joueur.h"

using namespace std;

const int LARGEUR_CARTE_DEFAUT = 1280;
const int HAUTEUR_CARTE_DEFAUT = 720;

Joueur::Joueur() {
    vie = 100;
    vitesse = 5;
    largeur = 40;
    hauteur = 40;

    pos.x = LARGEUR_CARTE_DEFAUT / 2 - largeur / 2;
    pos.y = HAUTEUR_CARTE_DEFAUT / 2 - hauteur / 2;
}

void Joueur::seDeplacer(const Uint8* etatClavier, int largeurCarte, int hauteurCarte, const vector<Ennemi>& ennemis) {
    float nouveauX = pos.x;
    float nouveauY = pos.y;

    if (etatClavier[SDL_SCANCODE_W]) {
        nouveauY -= vitesse;
    }
    if (etatClavier[SDL_SCANCODE_S]) {
        nouveauY += vitesse;
    }
    if (etatClavier[SDL_SCANCODE_A]) {
        nouveauX -= vitesse;
    }
    if (etatClavier[SDL_SCANCODE_D]) {
        nouveauX += vitesse;
    }

    if (nouveauX < 0) {
        nouveauX = 0;
    }
    if (nouveauY < 0) {
        nouveauY = 0;
    }
    if (nouveauX + largeur > largeurCarte) {
        nouveauX = largeurCarte - largeur;
    }
    if (nouveauY + hauteur > hauteurCarte) {
        nouveauY = hauteurCarte - hauteur;
    }

    SDL_Rect futurRect = getRectAvecPosition(nouveauX, nouveauY);
    bool collision = false;

    for (unsigned int i = 0; i < ennemis.size(); i++) {
        SDL_Rect rectEnnemi = ennemis[i].getRect();

        if (SDL_HasIntersection(&futurRect, &rectEnnemi)) {
            collision = true;
        }
    }

    if (!collision) {
        pos.x = nouveauX;
        pos.y = nouveauY;
    }
}

Position Joueur::getPosition() const {
    return pos;
}

int Joueur::getVie() const {
    return vie;
}

int Joueur::getLargeur() const {
    return largeur;
}

int Joueur::getHauteur() const {
    return hauteur;
}

SDL_Rect Joueur::getRect() const {
    SDL_Rect r;
    r.x = int(pos.x);
    r.y = int(pos.y);
    r.w = largeur;
    r.h = hauteur;
    return r;
}

SDL_Rect Joueur::getRectAvecPosition(float x, float y) const {
    SDL_Rect r;
    r.x = int(x);
    r.y = int(y);
    r.w = largeur;
    r.h = hauteur;
    return r;
}

void Joueur::tirer() {

} 