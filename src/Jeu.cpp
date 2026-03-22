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
    joueur.deplacerAvecDirection(commande, largeurCarte, hauteurCarte, ennemis);

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

Joueur& Jeu::getJoueur() {
    return joueur;
}

const Joueur& Jeu::getJoueur() const {
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