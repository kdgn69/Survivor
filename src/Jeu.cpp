#include "Jeu.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

Jeu::Jeu() {
    niveauActuel = 1;
    numeroVague = 1;
    largeurCarte = 40;
    hauteurCarte = 20;
}

void Jeu::initialiser() {
    srand((unsigned int)time(nullptr));
    genererEnnemisDebut();
}

void Jeu::updateConsole(char commande) {
    // Déplacement du joueur
    if (commande == 'z' || commande == 'q' || commande == 's' || commande == 'd') {
        joueur.deplacerAvecDirection(commande, largeurCarte, hauteurCarte, ennemis);
    }

    // Tir clavier pour la version console
    if (commande == 'i' || commande == 'j' || commande == 'k' || commande == 'l') {
        tirerConsole(commande);
    }

    // Les projectiles avancent après l'action du joueur
    deplacerProjectilesAllies();

    // On regarde ensuite s'ils touchent un ennemi
    gererCollisionsProjectilesEnnemis();

    // Puis les ennemis jouent leur tour
    Position posJoueur = joueur.getPosition();
    for (unsigned int i = 0; i < ennemis.size(); i++) {
        ennemis[i].seDeplacerVersJoueur(posJoueur, joueur.getLargeur(), joueur.getHauteur());
    }
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

void Jeu::tirerConsole(char commande) {
    int dx = 0;
    int dy = 0;

    if (commande == 'i') {
        dy = -1;
    }
    if (commande == 'k') {
        dy = 1;
    }
    if (commande == 'j') {
        dx = -1;
    }
    if (commande == 'l') {
        dx = 1;
    }

    Position posJoueur = joueur.getPosition();

    // Le projectile apparaît juste à côté du joueur
    float xDepart = posJoueur.x + dx;
    float yDepart = posJoueur.y + dy;

    // On évite de créer un projectile en dehors de la carte
    if (xDepart < 0 || xDepart >= largeurCarte || yDepart < 0 || yDepart >= hauteurCarte) {
        return;
    }

    Projectile p;
    p.initialiser(xDepart, yDepart, dx, dy);
    projectileAllie.push_back(p);
}

void Jeu::deplacerProjectilesAllies() {
    for (unsigned int i = 0; i < projectileAllie.size(); i++) {
        if (projectileAllie[i].estActif()) {
            projectileAllie[i].avancer();

            Position pos = projectileAllie[i].getPosition();

            // Si le projectile sort de la carte, on le supprime
            if (pos.x < 0 || pos.x >= largeurCarte || pos.y < 0 || pos.y >= hauteurCarte) {
                projectileAllie[i].desactiver();
            }
        }
    }

    vector<Projectile> nouveauxProjectiles;

    for (unsigned int i = 0; i < projectileAllie.size(); i++) {
        if (projectileAllie[i].estActif()) {
            nouveauxProjectiles.push_back(projectileAllie[i]);
        }
    }

    projectileAllie = nouveauxProjectiles;
}

void Jeu::gererCollisionsProjectilesEnnemis() {
    vector<Projectile> nouveauxProjectiles;
    vector<Ennemi> nouveauxEnnemis;

    vector<bool> ennemiTouche;
    ennemiTouche.resize(ennemis.size(), false);

    for (unsigned int i = 0; i < projectileAllie.size(); i++) {
        bool projectileATouche = false;
        Position posProjectile = projectileAllie[i].getPosition();

        for (unsigned int j = 0; j < ennemis.size(); j++) {
            Position posEnnemi = ennemis[j].getPosition();

            if (int(posProjectile.x) == int(posEnnemi.x) && int(posProjectile.y) == int(posEnnemi.y)) {
                projectileATouche = true;
                ennemiTouche[j] = true;
            }
        }

        if (!projectileATouche) {
            nouveauxProjectiles.push_back(projectileAllie[i]);
        }
    }

    for (unsigned int j = 0; j < ennemis.size(); j++) {
        if (!ennemiTouche[j]) {
            nouveauxEnnemis.push_back(ennemis[j]);
        }
    }

    projectileAllie = nouveauxProjectiles;
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
    return projectileAllie;
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