#include "Jeu.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;

const int TAILLE_CASE_SDL = 1;

Jeu::Jeu() {
    niveauActuel = 1;
    numeroVague = 1;
    largeurCarte = 1920;
    hauteurCarte = 1080;
}

void Jeu::initialiser() {
    srand(time(0));

    // On place le joueur au centre de la carte
    joueur.setPosition(largeurCarte / 2, hauteurCarte / 2);

    genererEnnemisDebut();
}

void Jeu::updateConsole(char commande) {
    if (commande == 'z' || commande == 'q' || commande == 's' || commande == 'd') {
        joueur.deplacerAvecDirection(commande, largeurCarte, hauteurCarte, ennemis);
    }

    deplacerProjectilesAllies();
    gererCollisionsProjectilesEnnemis();

    Position posJoueur = joueur.getPosition();
    for (unsigned int i = 0; i < ennemis.size(); i++) {
        ennemis[i].seDeplacerVersJoueur(posJoueur, joueur.getLargeur(), joueur.getHauteur());
    }

    gererCollisionsProjectilesEnnemis();
}

void Jeu::updateTirConsole(float angleDegres) {
    deplacerProjectilesAllies();
    gererCollisionsProjectilesEnnemis();

    tirerConsole(angleDegres);
    gererCollisionsProjectilesEnnemis();

    Position posJoueur = joueur.getPosition();
    for (unsigned int i = 0; i < ennemis.size(); i++) {
        ennemis[i].seDeplacerVersJoueur(posJoueur, joueur.getLargeur(), joueur.getHauteur());
    }

    gererCollisionsProjectilesEnnemis();
}

void Jeu::updateSDL(const Uint8* etatClavier) {
    // On réutilise la logique de déplacement du joueur
    if (etatClavier[SDL_SCANCODE_W]) {
        joueur.deplacerAvecDirection('z', largeurCarte, hauteurCarte, ennemis);
    }
    if (etatClavier[SDL_SCANCODE_S]) {
        joueur.deplacerAvecDirection('s', largeurCarte, hauteurCarte, ennemis);
    }
    if (etatClavier[SDL_SCANCODE_A]) {
        joueur.deplacerAvecDirection('q', largeurCarte, hauteurCarte, ennemis);
    }
    if (etatClavier[SDL_SCANCODE_D]) {
        joueur.deplacerAvecDirection('d', largeurCarte, hauteurCarte, ennemis);
    }

    deplacerProjectilesAllies();
    gererCollisionsProjectilesEnnemis();

    Position posJoueur = joueur.getPosition();
    for (unsigned int i = 0; i < ennemis.size(); i++) {
        ennemis[i].seDeplacerVersJoueur(posJoueur, joueur.getLargeur(), joueur.getHauteur());
    }

    gererCollisionsProjectilesEnnemis();
}

void Jeu::renderSDL(SDL_Renderer* rendu) const {
    // On vide l'écran
    SDL_SetRenderDrawColor(rendu, 30, 30, 30, 255);
    SDL_RenderClear(rendu);

    // Fond de la carte
    SDL_FRect fondCarte;
    fondCarte.x = 0;
    fondCarte.y = 0;
    fondCarte.w = largeurCarte * TAILLE_CASE_SDL;
    fondCarte.h = hauteurCarte * TAILLE_CASE_SDL;

    SDL_SetRenderDrawColor(rendu, 70, 120, 70, 255);
    SDL_RenderFillRectF(rendu, &fondCarte);

    // Bordure rouge pour voir les limites de la map
    SDL_SetRenderDrawColor(rendu, 220, 40, 40, 255);
    SDL_RenderDrawRectF(rendu, &fondCarte);

    // Affichage du joueur
    Position posJoueur = joueur.getPosition();

    SDL_FRect rectJoueur;
    rectJoueur.x = posJoueur.x * TAILLE_CASE_SDL;
    rectJoueur.y = posJoueur.y * TAILLE_CASE_SDL;
    rectJoueur.w = joueur.getLargeur() * TAILLE_CASE_SDL;
    rectJoueur.h = joueur.getHauteur() * TAILLE_CASE_SDL;

    SDL_SetRenderDrawColor(rendu, 50, 100, 255, 255);
    SDL_RenderFillRectF(rendu, &rectJoueur);

    // Affichage des ennemis
    for (unsigned int i = 0; i < ennemis.size(); i++) {
        Position posEnnemi = ennemis[i].getPosition();

        SDL_Rect rectEnnemi;
        rectEnnemi.x = int(posEnnemi.x * TAILLE_CASE_SDL);
        rectEnnemi.y = int(posEnnemi.y * TAILLE_CASE_SDL);
        rectEnnemi.w = ennemis[i].getLargeur() * TAILLE_CASE_SDL;
        rectEnnemi.h = ennemis[i].getHauteur() * TAILLE_CASE_SDL;

        SDL_SetRenderDrawColor(rendu, 120, 50, 50, 255);
        SDL_RenderFillRect(rendu, &rectEnnemi);
    }

    // Affichage des projectiles déjà existants
    for (unsigned int i = 0; i < projectilesAllies.size(); i++) {
        Position posProjectile = projectilesAllies[i].getPosition();

        SDL_Rect rectProjectile;
        rectProjectile.x = int(posProjectile.x * TAILLE_CASE_SDL + TAILLE_CASE_SDL / 4);
        rectProjectile.y = int(posProjectile.y * TAILLE_CASE_SDL + TAILLE_CASE_SDL / 4);
        rectProjectile.w = TAILLE_CASE_SDL / 2;
        rectProjectile.h = TAILLE_CASE_SDL / 2;

        SDL_SetRenderDrawColor(rendu, 255, 230, 80, 255);
        SDL_RenderFillRect(rendu, &rectProjectile);
    }
}

void Jeu::genererEnnemisDebut() {
    ennemis.clear();

    Position posJoueur = joueur.getPosition();
    int centreJoueurX = int(posJoueur.x) + joueur.getLargeur() / 2;
    int centreJoueurY = int(posJoueur.y) + joueur.getHauteur() / 2;

    for (int i = 0; i < 6; i++) {
        bool positionValide = false;
        float x = 0;
        float y = 0;

        while (!positionValide) {
            x = rand() % largeurCarte;
            y = rand() % hauteurCarte;

            int centreEnnemiX = int(x);
            int centreEnnemiY = int(y);

            float dx = centreEnnemiX - centreJoueurX;
            float dy = centreEnnemiY - centreJoueurY;
            float distance = sqrt(dx * dx + dy * dy);

            // On évite de faire apparaître les ennemis trop près du joueur
            if (distance >= 5) {
                positionValide = true;
            }
        }
        ennemis.push_back(Ennemi(x, y, "zombie", false, 100, 3, 15, 15));
    }
}

void Jeu::tirerConsole(float angleDegres) {
    float angleRadians = angleDegres * 3.14159265f / 180.0f;

    float dx = cos(angleRadians);
    float dy = -sin(angleRadians);

    Position posJoueur = joueur.getPosition();

    float xDepart = posJoueur.x + dx;
    float yDepart = posJoueur.y + dy;

    if (xDepart < 0 || xDepart >= largeurCarte || yDepart < 0 || yDepart >= hauteurCarte) {
        return;
    }

    Projectile p;
    p.initialiser(xDepart, yDepart, dx, dy);
    projectilesAllies.push_back(p);
}

void Jeu::deplacerProjectilesAllies() {
    for (unsigned int i = 0; i < projectilesAllies.size(); i++) {
        if (projectilesAllies[i].estActif()) {
            projectilesAllies[i].avancer();

            Position pos = projectilesAllies[i].getPosition();

            // Si le projectile sort de la carte, on le désactive
            if (pos.x < 0 || pos.x >= largeurCarte || pos.y < 0 || pos.y >= hauteurCarte) {
                projectilesAllies[i].desactiver();
            }
        }
    }

    vector<Projectile> nouveauxProjectiles;

    for (unsigned int i = 0; i < projectilesAllies.size(); i++) {
        if (projectilesAllies[i].estActif()) {
            nouveauxProjectiles.push_back(projectilesAllies[i]);
        }
    }

    projectilesAllies = nouveauxProjectiles;
}

void Jeu::gererCollisionsProjectilesEnnemis() {
    vector<Projectile> nouveauxProjectiles;
    vector<Ennemi> nouveauxEnnemis;
    vector<bool> ennemiTouche(ennemis.size(), false);

    for (unsigned int i = 0; i < projectilesAllies.size(); i++) {
        bool projectileATouche = false;
        Position posProjectile = projectilesAllies[i].getPosition();

        for (unsigned int j = 0; j < ennemis.size(); j++) {
            Position posEnnemi = ennemis[j].getPosition();

            if (int(posProjectile.x) == int(posEnnemi.x) && int(posProjectile.y) == int(posEnnemi.y)) {
                projectileATouche = true;
                ennemiTouche[j] = true;
            }
        }

        if (!projectileATouche) {
            nouveauxProjectiles.push_back(projectilesAllies[i]);
        }
    }

    for (unsigned int j = 0; j < ennemis.size(); j++) {
        if (!ennemiTouche[j]) {
            nouveauxEnnemis.push_back(ennemis[j]);
        }
    }

    projectilesAllies = nouveauxProjectiles;
    ennemis = nouveauxEnnemis;
}

Joueur& Jeu::getJoueur() {
    return joueur;
}

const Joueur& Jeu::getJoueur() const {
    return joueur;
}

const vector<Ennemi>& Jeu::getEnnemis() const {
    return ennemis;
}

const vector<Projectile>& Jeu::getProjectilesAllies() const {
    return projectilesAllies;
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