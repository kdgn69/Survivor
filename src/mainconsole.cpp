#include <iostream>
#include <vector>
#include <string>
#include "Jeu.h"

using namespace std;

void afficherJeuConsole(const Jeu& jeu) {
    int largeur = jeu.getLargeurCarte();
    int hauteur = jeu.getHauteurCarte();

    vector<string> grille(hauteur, string(largeur, '.'));

    Position posJoueur = jeu.getJoueur().getPosition();
    grille[int(posJoueur.y)][int(posJoueur.x)] = 'J';

    const vector<Ennemi>& ennemis = jeu.getEnnemis();
    for (unsigned int i = 0; i < ennemis.size(); i++) {
        Position posEnnemi = ennemis[i].getPosition();

        if (int(posEnnemi.y) >= 0 && int(posEnnemi.y) < hauteur &&
            int(posEnnemi.x) >= 0 && int(posEnnemi.x) < largeur) {
            grille[int(posEnnemi.y)][int(posEnnemi.x)] = 'E';
        }
    }

    const vector<Projectile>& projectiles = jeu.getProjectilesAllies();
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        Position posProjectile = projectiles[i].getPosition();

        if (int(posProjectile.y) >= 0 && int(posProjectile.y) < hauteur &&
            int(posProjectile.x) >= 0 && int(posProjectile.x) < largeur) {
            grille[int(posProjectile.y)][int(posProjectile.x)] = '*';
        }
    }

    cout << "Niveau " << jeu.getNiveauActuel() << " - Vague " << jeu.getNumeroVague() << endl;
    cout << endl;

    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            cout << grille[y][x];
        }
        cout << endl;
    }

    cout << endl;
    cout << "Deplacement : z q s d" << endl;
    cout << "Tir : t puis angle" << endl;
    cout << "Quitter : x" << endl;
}

int main() {
    Jeu jeu;
    jeu.initialiser();

    char commande = ' ';

    while (commande != 'x') {
        cout << string(30, '\n');

        afficherJeuConsole(jeu);
        cin >> commande;

        if (commande == 't') {
            float angle;
            cout << "Angle de tir : ";
            cin >> angle;
            jeu.updateTirConsole(angle);
        }
        else {
            jeu.updateConsole(commande);
        }
    }

    return 0;
}