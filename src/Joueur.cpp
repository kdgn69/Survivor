#include <iostream>
#include "Joueur.h"

using namespace std;

const int LARGEUR_FENETRE = 1920;
const int HAUTEUR_FENETRE = 1080;

Joueur::Joueur() {
    vie = 100;
    vitesse = 5;
    pos.x = LARGEUR_FENETRE / 2;
    pos.y = HAUTEUR_FENETRE / 2;
}

void Joueur::seDeplacer(const Uint8* etatClavier) { //on pourrait aussi creer une struct "touches" pour alleger le code ici
    if (etatClavier[SDL_SCANCODE_Z]) {
        pos.y -= vitesse;
    }
    if (etatClavier[SDL_SCANCODE_S]) {
        pos.y += vitesse;
    }
    if (etatClavier[SDL_SCANCODE_Q]) {
        pos.x -= vitesse;
    }
    if (etatClavier[SDL_SCANCODE_D]) {
        pos.x += vitesse;
    }

    if (pos.x < 0) {
        pos.x = 0;
    }
    if (pos.y < 0) {
        pos.y = 0;
    }
    if (pos.x > LARGEUR_FENETRE) {
        pos.x = LARGEUR_FENETRE;
    }
    if (pos.y > HAUTEUR_FENETRE) {
        pos.y = HAUTEUR_FENETRE;
    }
}

void Joueur::tirer() {

}