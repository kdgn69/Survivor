#ifndef JEUCONSOLE_H
#define JEUCONSOLE_H

#include "../Jeu.h"

using namespace std;

// Affiche la grille texte du jeu
void afficherJeuConsole(const Jeu& jeu);

// Gère la boucle complète du mode texte
void Boucle(Jeu& jeu);

#endif 