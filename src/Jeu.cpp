#include "Jeu.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

Jeu::Jeu() {
    niveauActuel = 1;
    numeroVague = 1;
    largeurCarte = 1920;
    hauteurCarte = 1080;
}

void Jeu::initialiser() {
    srand(time(0));
    joueur.setPosition(largeurCarte / 2, hauteurCarte / 2);
    genererEnnemisDebut();
}

void Jeu::genererEnnemisDebut() {
    ennemis.clear();
    genererEnnemis(6, "zombie", false, 5, 2, 20, 20, 100);
}

void Jeu::genererEnnemis(int nombre, const string& type, bool attaqueDistance, int pv, float vitesse, int largeur, int hauteur, float distanceMinJoueur) {
    Position posJoueur = joueur.getPosition();

    float demiLargeur = largeur / 2;
    float demiHauteur = hauteur / 2;

    for (int i = 0; i < nombre; i++) {
        bool positionValide = false;
        float centreX = 0;
        float centreY = 0;

        while (!positionValide) {
            centreX = demiLargeur + rand() % int(largeurCarte - largeur);
            centreY = demiHauteur + rand() % int(hauteurCarte - hauteur);

            float dx = centreX - posJoueur.x;
            float dy = centreY - posJoueur.y;
            float distance = sqrt(dx * dx + dy * dy);

            //Pour ne pas faire spawn l'ennemi trop près du joueur
            if (distance >= distanceMinJoueur) {
                positionValide = true;
            }
        }

        Ennemi e(centreX, centreY, type, attaqueDistance, pv, vitesse, largeur, hauteur);
        ennemis.push_back(e);
    }
}

void Jeu::deplacerJoueur(char direction) {
    if (direction == 'z' || direction == 'q' || direction == 's' || direction == 'd') {
        joueur.deplacerAvecDirection(direction, largeurCarte, hauteurCarte, ennemis);
    }
}

void Jeu::tirer(float angleDegres) {
    const Arme& arme = joueur.getArme();

    float angleRadians = angleDegres * 3.14159265 / 180;

    float vitesseProjectile = arme.getVitesseProjectile();
    float dx = cos(angleRadians) * vitesseProjectile;
    float dy = -sin(angleRadians) * vitesseProjectile;

    Position posJoueur = joueur.getPosition();

    float largeur = arme.getLargeurProjectile();
    float hauteur = arme.getHauteurProjectile();

    int degats = arme.getDegats();

    Projectile p(posJoueur.x, posJoueur.y, dx, dy, degats, largeur, hauteur);
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