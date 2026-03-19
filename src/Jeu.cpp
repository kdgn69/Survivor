#include "Jeu.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;

Jeu::Jeu() {
    niveauActuel = 1;
    numeroVague = 1;
    largeurCarte = 1280;
    hauteurCarte = 720;
}

void Jeu::initialiser() {
    srand((unsigned int)time(nullptr));
    genererEnnemisDebut();
}

void Jeu::update(const Uint8* etatClavier) {
    joueur.seDeplacer(etatClavier, largeurCarte, hauteurCarte);

    Position posJoueur = joueur.getPosition();

    for (unsigned int i = 0; i < ennemis.size(); i++) {
        ennemis[i].seDeplacerVersJoueur(posJoueur, joueur.getLargeur(), joueur.getHauteur());
    }
} 

void Jeu::genererEnnemisDebut() {
    ennemis.clear();

    Position posJoueur = joueur.getPosition();
    int centreJoueurX = (int)posJoueur.x + joueur.getLargeur() / 2;
    int centreJoueurY = (int)posJoueur.y + joueur.getHauteur() / 2;

    for (int i = 0; i < 6; i++) {
        Ennemi e;

        bool positionValide = false;
        float x = 0;
        float y = 0;

        while (!positionValide) {
            x = rand() % (largeurCarte - 30);
            y = rand() % (hauteurCarte - 30);

            int centreEnnemiX = (int)x + 15;
            int centreEnnemiY = (int)y + 15;

            float dx = centreEnnemiX - centreJoueurX;
            float dy = centreEnnemiY - centreJoueurY;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance >= 100) {
                positionValide = true;
            }
        }

        e.initialiser(x, y, "zombie", false, 100, 1, 30, 30);
        ennemis.push_back(e);
    }
}

void Jeu::render(SDL_Renderer* rendu) const {
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
    SDL_RenderClear(rendu);

    SDL_Rect fondCarte = {0, 0, largeurCarte, hauteurCarte};
    SDL_SetRenderDrawColor(rendu, 70, 120, 70, 255);
    SDL_RenderFillRect(rendu, &fondCarte);

    SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
    SDL_RenderDrawRect(rendu, &fondCarte);

    SDL_Rect rectJoueur = joueur.getRect();
    SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255);
    SDL_RenderFillRect(rendu, &rectJoueur);

    for (unsigned int i = 0; i < ennemis.size(); i++) {
        SDL_Rect rectEnnemi = ennemis[i].getRect();
        SDL_SetRenderDrawColor(rendu, 80, 40, 40, 255);
        SDL_RenderFillRect(rendu, &rectEnnemi);
    }
}

Joueur& Jeu::getJoueur() {
    return joueur;
}

const vector<Ennemi>& Jeu::getEnnemis() const {
    return ennemis;
}

int Jeu::getNiveauActuel() const {
    return niveauActuel;
}

int Jeu::getNumeroVague() const {
    return numeroVague;
}

int Jeu::getLargeurCarte() const {
    return largeurCarte;
}

int Jeu::getHauteurCarte() const {
    return hauteurCarte;
}