#include "Jeu.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;

Jeu::Jeu() {
    niveauActuel = 1;
    numeroVague = 1;
    largeurCarte = 40;
    hauteurCarte = 20;
}

void Jeu::initialiser() {
    srand(time(0));

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

void Jeu::genererEnnemisDebut() {
    ennemis.clear();

    Position posJoueur = joueur.getPosition();
    int centreJoueurX = int(posJoueur.x) + joueur.getLargeur() / 2;
    int centreJoueurY = int(posJoueur.y) + joueur.getHauteur() / 2;

    for (int i = 0; i < 6; i++) {
        Ennemi e;
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

            if (distance >= 5) {
                positionValide = true;
            }
        }

        e.initialiser(x, y, "zombie", false, 100, 1, 1, 1);
        ennemis.push_back(e);
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