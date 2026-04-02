#include "Jeu.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

Jeu::Jeu(int largeur, int hauteur) {
    niveauActuel = 1;
    numeroVague = 1;
    largeurCarte = largeur;
    hauteurCarte = hauteur;
}

void Jeu::initialiser() {
    srand(time(0));
    joueur.setPosition(largeurCarte / 2, hauteurCarte / 2);
    genererEnnemisDebut();
}

void Jeu::genererEnnemisDebut() {
    ennemis.clear();

    Position posJoueur = joueur.getPosition();
    float centreJoueurX = posJoueur.x + joueur.getLargeur() / 2;
    float centreJoueurY = posJoueur.y + joueur.getHauteur() / 2;

    for (int i = 0; i < 6; i++) {
        bool positionValide = false;
        float x = 0;
        float y = 0;

        while (!positionValide) {
            x = rand() % largeurCarte;
            y = rand() % hauteurCarte;

            float centreEnnemiX = x;
            float centreEnnemiY = y;

            float dx = centreEnnemiX - centreJoueurX;
            float dy = centreEnnemiY - centreJoueurY;
            float distance = sqrt(dx * dx + dy * dy);

            // On évite de faire apparaître un ennemi trop près du joueur
            if (distance >= 100) {
                positionValide = true;
            }
        }

        Ennemi e(x, y, "zombie", false, 5, 2, 20, 20);
        ennemis.push_back(e);
    }
}

void Jeu::deplacerJoueur(char direction) {
    if (direction == 'z' || direction == 'q' || direction == 's' || direction == 'd') {
        joueur.deplacerAvecDirection(direction, largeurCarte, hauteurCarte, ennemis);
    }
}

void Jeu::tirer(float angleDegres) {
    float angleRadians = angleDegres * 3.14159265f / 180;

    float dx = cos(angleRadians) * 3;
    float dy = -sin(angleRadians) * 3;

    Position posJoueur = joueur.getPosition();

    float centreJoueurX = posJoueur.x + joueur.getLargeur() / 2;
    float centreJoueurY = posJoueur.y + joueur.getHauteur() / 2;

    float xDepart = centreJoueurX;
    float yDepart = centreJoueurY;

    // Si le projectile démarre hors de la carte, on annule
    if (xDepart < 0 || xDepart >= largeurCarte || yDepart < 0 || yDepart >= hauteurCarte) {
        return;
    }

    Projectile p(xDepart, yDepart, dx, dy, 10, 5, 5);
    projectilesAllies.push_back(p);
}

void Jeu::avancerTour() {
    // Les projectiles avancent d'abord
    deplacerProjectilesAllies();
    gererCollisionsProjectilesAllieSurLesEnnemis();

    // Puis les ennemis jouent leur tour
    Position posJoueur = joueur.getPosition();
    for (unsigned int i = 0; i < ennemis.size(); i++) {
        ennemis[i].seDeplacerVersJoueur(posJoueur, joueur.getLargeur(), joueur.getHauteur());
    }

    gererCollisionsProjectilesAllieSurLesEnnemis();
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

void Jeu::gererCollisionsProjectilesAllieSurLesEnnemis() {
    vector<Projectile> nouveauxProjectiles;
    vector<Ennemi> nouveauxEnnemis;

    // On parcourt tous les projectiles
    for (unsigned int i = 0; i < projectilesAllies.size(); i++) {
        bool projectileATouche = false;
        Rectangle rectProjectile = projectilesAllies[i].getRectangle();

        // On teste collision avec chaque ennemi
        for (unsigned int j = 0; j < ennemis.size(); j++) {
            Rectangle rectEnnemi = ennemis[j].getRectangle();

            if (collisionRectangles(rectProjectile, rectEnnemi)) {
                // on enlève des PV à l'ennemi
                ennemis[j].prendreDegats(projectilesAllies[i].getDegats());

                projectileATouche = true;
                break; // un projectile ne touche qu'un ennemi
            }
        }
        // si le projectile n'a rien touché, on le garde
        if (!projectileATouche) {
            nouveauxProjectiles.push_back(projectilesAllies[i]);
        }
    }
    // on garde seulement les ennemis encore en vie
    for (unsigned int j = 0; j < ennemis.size(); j++) {
        if (!ennemis[j].estMort()) {
            nouveauxEnnemis.push_back(ennemis[j]);
        }
    }
    // mise à jour des listes
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