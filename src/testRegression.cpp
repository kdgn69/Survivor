#include <iostream>
#include <cassert>
#include <vector>
#include "Rectangle.h"
#include "Projectile.h"
#include "Joueur.h"
#include "Ennemi.h"

using namespace std;

void testCollisionRectangles() {
    Rectangle a = {0, 0, 2, 2};
    Rectangle b = {1, 1, 2, 2};
    Rectangle c = {5, 5, 2, 2};

    assert(collisionRectangles(a, b) == true);
    assert(collisionRectangles(a, c) == false);

    cout << "testCollisionRectangles OK" << endl;
}

void testProjectileAvance() {
    Projectile p;
    p.initialiser(5, 5, 1, 0);
    p.avancer();

    Position pos = p.getPosition();

    assert(int(pos.x) == 6);
    assert(int(pos.y) == 5);

    cout << "testProjectileAvance OK" << endl;
}

void testJoueurBloqueParBord() {
    Joueur j;
    vector<Ennemi> ennemis;

    j.setPosition(0, 0);
    j.deplacerAvecDirection('q', 40, 20, ennemis);
    j.deplacerAvecDirection('z', 40, 20, ennemis);

    Position pos = j.getPosition();

    assert(int(pos.x) == 0);
    assert(int(pos.y) == 0);

    cout << "testJoueurBloqueParBord OK" << endl;
}

void testEnnemiSeRapprocheDuJoueur() {
    Ennemi e(10, 10, "zombie", false, 100, 1, 1, 1);

    Position posJoueur;
    posJoueur.x = 15;
    posJoueur.y = 10;

    e.seDeplacerVersJoueur(posJoueur, 1, 1);

    Position posEnnemi = e.getPosition();

    assert(posEnnemi.x > 10);
    assert(int(posEnnemi.y) == 10);

    cout << "testEnnemiSeRapprocheDuJoueur OK" << endl;
}

int main() {
    testCollisionRectangles();
    testProjectileAvance();
    testJoueurBloqueParBord();
    testEnnemiSeRapprocheDuJoueur();

    cout << endl;
    cout << "Tous les tests de regression sont passes." << endl;

    return 0;
}