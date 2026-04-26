#include "Jeu.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

Jeu::Jeu() {
    largeurCarte = 1920;
    hauteurCarte = 1080;
    enChoixAmelioration = false;
    niveauMultitir = 0;
    niveauAuraMorts = 0;
    niveauAuraJoueur = 0;
    niveauFoudre = 0;
    tirPerforantActif = false;
}

void Jeu::initialiser() {
    srand(time(0));
    joueur.setPosition(largeurCarte / 2, hauteurCarte / 2);
    genererVagueActuelle();
}

void Jeu::avancerTour() {
    if (enChoixAmelioration) {
        return;
    }

    deplacerProjectilesAllies();
    gererCollisionsProjectilesAllieSurLesEnnemis();
    gererMortsEnnemis();
    deplacerEnnemisVersJoueur();
    mettreAJourAuras();
    mettreAJourEtatAuraJoueur();
    appliquerDegatsDesAuras();
    deplacerProjectilesEnnemis();
    gererCollisionsProjectilesEnnemisSurJoueur();

    if (ennemis.empty()) {
        genererChoixAmeliorations();
    }
}

void Jeu::genererVagueActuelle() {
    ennemis.clear();
    int nombre = vague.getNombreEnnemis();
    genererEnnemis(nombre, ARCHER, 100, 0.4, 20, 20, 500);
}

void Jeu::genererEnnemis(int nombre, TypeEnnemi type, int pv, float vitesse, int largeur, int hauteur, float distanceMinJoueur) {
    Position posJoueur = joueur.getPosition();

    for (int i = 0; i < nombre; i++) {
        bool positionValide = false;
        float centreX = 0;
        float centreY = 0;

        while (!positionValide) {
            centreX = posJoueur.x + (rand() % 2500 - 1250);
            centreY = posJoueur.y + (rand() % 2500 - 1250);

            float dx = centreX - posJoueur.x;
            float dy = centreY - posJoueur.y;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance >= distanceMinJoueur) {
                positionValide = true;
            }
        }
        Ennemi e(centreX, centreY, type, pv, vitesse, largeur, hauteur);
        ennemis.push_back(e);
    }
}

void Jeu::deplacerJoueur(char direction) {
    if (enChoixAmelioration) return;
    
    joueur.deplacerAvecDirection(direction, ennemis);
}

void Jeu::deplacerEnnemisVersJoueur() {
    Position posJoueur = joueur.getPosition();

    for (unsigned int i = 0; i < ennemis.size(); i++) {
        ennemis[i].seDeplacerVersJoueur(posJoueur, joueur.getLargeur(), joueur.getHauteur());
    }
}

void Jeu::tirer(float angleDegres) {
    if (enChoixAmelioration) {
        return;
    }

    const Arme& arme = joueur.getArme();

    Position posJoueur = joueur.getPosition();

    float largeur = arme.getLargeurProjectile();
    float hauteur = arme.getHauteurProjectile();
    float vitesseProjectile = arme.getVitesseProjectile();
    int degats = arme.getDegats();

    vector<float> angles;

    // niveau 0 : tir normal
    if (niveauMultitir == 0) {
        angles.push_back(angleDegres);
    }
    // niveau 1 : 3 tirs
    else if (niveauMultitir == 1) {
        angles.push_back(angleDegres - 20);
        angles.push_back(angleDegres);
        angles.push_back(angleDegres + 20);
    }
    // niveau 2 : 5 tirs
    else if (niveauMultitir >= 2) {
        angles.push_back(angleDegres - 30);
        angles.push_back(angleDegres - 20);
        angles.push_back(angleDegres);
        angles.push_back(angleDegres + 20);
        angles.push_back(angleDegres + 30);
    }

    // on crée un projectile pour chaque angle (multitir)
    for (unsigned int i = 0; i < angles.size(); i++) {
        // conversion de l'angle en radians
        float angleRad = angles[i] * 3.14159265 / 180;

        // calcul de la direction du projectile
        // cos = déplacement horizontal et sin = déplacement vertical
        float dx = cos(angleRad) * vitesseProjectile;
        float dy = -sin(angleRad) * vitesseProjectile;

        Projectile p(posJoueur.x, posJoueur.y, dx, dy, degats, largeur, hauteur);
        if (joueur.aTirPerforant()) {
            p.setPerforant(true);
        }
        projectilesAllies.push_back(p);
    }
}

void Jeu::faireTirerEnnemis(float maintenant) {
    Position posJoueur = joueur.getPosition();

    for (unsigned int i = 0; i < ennemis.size(); i++) {

        if (ennemis[i].getType() != ARCHER) continue;

        float intervalle = ennemis[i].getArme().getIntervalleTirMs();
        if (maintenant - ennemis[i].getDernierTir() < intervalle) continue;

        Projectile p = creerProjectileDepuisEnnemi(ennemis[i], posJoueur);
        projectilesEnnemis.push_back(p);

        ennemis[i].setDernierTir(maintenant);
    }
}

Projectile Jeu::creerProjectileDepuisEnnemi(const Ennemi& ennemi, const Position& cible) const {
    Position pos = ennemi.getPosition();

    float dx = cible.x - pos.x;
    float dy = cible.y - pos.y;

    float distance = sqrt(dx * dx + dy * dy);
    if (distance == 0) distance = 1;

    dx /= distance;
    dy /= distance;

    const Arme& arme = ennemi.getArme();

    float vitesse = arme.getVitesseProjectile();
    int degats = arme.getDegats();
    float largeur = arme.getLargeurProjectile();
    float hauteur = arme.getHauteurProjectile();

    return Projectile(pos.x, pos.y, dx * vitesse, dy * vitesse, degats, largeur, hauteur);
}

void Jeu::deplacerProjectilesAllies() {
    for (unsigned int i = 0; i < projectilesAllies.size(); i++) {
        if (projectilesAllies[i].estActif()) {
            projectilesAllies[i].avancer();
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

void Jeu::deplacerProjectilesEnnemis() {
    for (unsigned int i = 0; i < projectilesEnnemis.size(); i++) {
        if (projectilesEnnemis[i].estActif()) {
            projectilesEnnemis[i].avancer();
        }
    }
    vector<Projectile> nouveaux;

    for (unsigned int i = 0; i < projectilesEnnemis.size(); i++) {
        if (projectilesEnnemis[i].estActif()) {
            nouveaux.push_back(projectilesEnnemis[i]);
        }
    }
    projectilesEnnemis = nouveaux;
}

void Jeu::gererCollisionsProjectilesAllieSurLesEnnemis() {
    vector<Projectile> nouveauxProjectiles;

    // On parcourt tous les projectiles
    for (unsigned int i = 0; i < projectilesAllies.size(); i++) {
        bool projectileATouche = false;
        Rectangle rectProjectile = projectilesAllies[i].getRectangle();

        // test collision avec ennemis
        for (unsigned int j = 0; j < ennemis.size(); j++) {
            Rectangle rectEnnemi = ennemis[j].getRectangle();

            if (collisionRectangles(rectProjectile, rectEnnemi)) {
                ennemis[j].prendreDegats(projectilesAllies[i].getDegats());

                if (!projectilesAllies[i].estPerforant()) {
                    projectileATouche = true;
                    break;
                }
            }
        }
        // si le projectile n’a pas touché, on le garde
        if (!projectileATouche) {
            nouveauxProjectiles.push_back(projectilesAllies[i]);
        }
    }
    // mise à jour des projectiles
    projectilesAllies = nouveauxProjectiles;
}

void Jeu::gererCollisionsProjectilesEnnemisSurJoueur() {
    Rectangle rectJoueur = joueur.getRectangle();
    vector<Projectile> nouveaux;

    for (unsigned int i = 0; i < projectilesEnnemis.size(); i++) {
        Rectangle rectP = projectilesEnnemis[i].getRectangle();

        if (collisionRectangles(rectP, rectJoueur)) {
            // dégâts joueur
            // joueur.prendreDegats(...)
        } else {
            nouveaux.push_back(projectilesEnnemis[i]);
        }
    }
    projectilesEnnemis = nouveaux;
}

void Jeu::ajouterProjectileEnnemi(const Projectile& p) {
    projectilesEnnemis.push_back(p);
}

void Jeu::genererChoixAmeliorations() {
    // on vide les anciens choix (au cas ou)
    choixAmeliorations.clear();

    // liste des améliorations possibles pour l'instant
    vector<string> nomsPossibles;
    nomsPossibles.push_back("degats");
    nomsPossibles.push_back("cadence");
    nomsPossibles.push_back("taille");
    nomsPossibles.push_back("vitesseProjectile");
    nomsPossibles.push_back("vitesseJoueur");
    nomsPossibles.push_back("multitir");
    nomsPossibles.push_back("auraMort");
    nomsPossibles.push_back("perforant");
    nomsPossibles.push_back("auraJoueur");
    nomsPossibles.push_back("foudre");

    // on veut exactement 3 choix différents
    while (choixAmeliorations.size() < 3) {
        // on choisit un type au hasard
        int indexAleatoire = rand() % nomsPossibles.size();
        string nomChoisi = nomsPossibles[indexAleatoire];

        // on vérifie qu'on ne l'a pas déjà pris (pour éviter les doublons)
        bool dejaPresent = false;
        for (unsigned int i = 0; i < choixAmeliorations.size(); i++) {
            if (choixAmeliorations[i].nom == nomChoisi) {
                dejaPresent = true;
                break;
            }
        }
        // si pas encore présent, on l'ajoute
        if (!dejaPresent) {
            // on empêche d'afficher les ameliorations si elles ont été prises le nombre max de fois possible
            if (nomChoisi == "multitir" && niveauMultitir >= 2) {
                continue;
            }
            if (nomChoisi == "auraMort" && niveauAuraMorts >= 3) {
                continue;
            }
            if (nomChoisi == "perforant" && tirPerforantActif) {
                continue;
            }
            if (nomChoisi == "auraJoueur" && niveauAuraJoueur >= 3) {
                continue;
            }
            if (nomChoisi == "foudre" && niveauFoudre >= 3) {
                continue;
            }
            Amelioration a;
            a.nom = nomChoisi;
            choixAmeliorations.push_back(a);
        }
    }
    // on passe en mode "choix d'amélioration"
    enChoixAmelioration = true;
}

void Jeu::appliquerAmeliorationChoisie(int index) {
    // on récupère l'arme du joueur (pour la modifier directement)
    Arme& arme = joueur.getArme();

    // on récupère le type d'amélioration choisi
    string nom = choixAmeliorations[index].nom;

    // en fonction du type, on applique l'effet
    if (nom == "degats") {
        arme.augmenterDegats(5);
    }
    else if (nom == "cadence") {
        arme.augmenterCadence(1);
    }
    else if (nom == "taille") {
        arme.augmenterLargeurProjectile(2);
        arme.augmenterHauteurProjectile(3);
    }
    else if (nom == "vitesseProjectile") {
        arme.augmenterVitesseProjectile(1);
    }
    else if (nom == "vitesseJoueur") {
        joueur.augmenterVitesse(0.01);
    }
    else if (nom == "multitir") {
        niveauMultitir++;
    }
    else if (nom == "auraMort") {
        niveauAuraMorts++;
    }
    else if (nom == "perforant") {
        joueur.activerTirPerforant();
        tirPerforantActif = true;
    }
    else if (nom == "auraJoueur") {
        niveauAuraJoueur++;
    }
    else if (nom == "foudre") {
        niveauFoudre++;
    }

    // une fois le choix fait, on sort du mode amélioration
    enChoixAmelioration = false;

    // on nettoie la liste
    choixAmeliorations.clear();
}

void Jeu::lancerVagueSuivante() {
    vague.passerSuivante();
    genererVagueActuelle();
}

void Jeu::gererMortsEnnemis() {
    vector<Ennemi> nouveauxEnnemis;

    for (unsigned int i = 0; i < ennemis.size(); i++) {
        if (ennemis[i].estMort()) {
            if (niveauAuraMorts > 0) {
                Position pos = ennemis[i].getPosition();

                float rayon = 40;
                int degats = 5;
                float duree = 300;
                float intervalle = 30;

                if (niveauAuraMorts == 2) {
                    rayon = 50;
                    degats = 8;
                    duree = 400;
                    intervalle = 25;
                }
                else if (niveauAuraMorts >= 3) {
                    rayon = 60;
                    degats = 12;
                    duree = 500;
                    intervalle = 20;
                }
                Aura a(pos.x, pos.y, rayon, degats, duree, intervalle, AURA_MORT);
                auras.push_back(a);
            }
        }
        else {
            nouveauxEnnemis.push_back(ennemis[i]);
        }
    }
    ennemis = nouveauxEnnemis;
}

//supp les auras qui sont expirées
void Jeu::mettreAJourAuras() {
    vector<Aura> nouvellesAuras;

    for (unsigned int i = 0; i < auras.size(); i++) {
        auras[i].mettreAJour();
        // on garde seulement les auras encore actives
        if (!auras[i].estExpiree()) {
            nouvellesAuras.push_back(auras[i]);
        }
    }
    auras = nouvellesAuras;
}

void Jeu::mettreAJourEtatAuraJoueur() {

    if (niveauAuraJoueur == 0) return;

    Position pos = joueur.getPosition();

    // stats selon le niveau
    float rayon = 150;
    int degats = 3;
    float intervalle = 50;

    if (niveauAuraJoueur == 2) {
        rayon = 200;
        degats = 6;
    }
    else if (niveauAuraJoueur >= 3) {
        rayon = 250;
        degats = 10;
        intervalle = 25;
    }

    bool trouve = false;

    // on cherche l'aura du joueur
    for (unsigned int i = 0; i < auras.size(); i++) {
        if (auras[i].getType() == AURA_JOUEUR) {

            // mise à jour position + stats
            auras[i].setPosition(pos.x, pos.y);
            auras[i].setRayon(rayon);
            auras[i].setDegats(degats);
            auras[i].setIntervalle(intervalle);

            trouve = true;
            break;
        }
    }

    // si aucune aura joueur n'existe encore, on la crée
    if (!trouve) {
        Aura auraJoueur(pos.x, pos.y, rayon, degats, 9999, intervalle, AURA_JOUEUR);
        auras.push_back(auraJoueur);
    }
}

void Jeu::appliquerDegatsDesAuras() {

    for (unsigned int i = 0; i < auras.size(); i++) {

        if (auras[i].peutInfligerDegats()) {

            Position posAura = auras[i].getPosition();
            float rayon = auras[i].getRayon();

            for (unsigned int j = 0; j < ennemis.size(); j++) {

                Position posEnnemi = ennemis[j].getPosition();

                float dx = posEnnemi.x - posAura.x;
                float dy = posEnnemi.y - posAura.y;
                float distance = sqrt(dx * dx + dy * dy);

                if (distance <= rayon) {
                    ennemis[j].prendreDegats(auras[i].getDegats());
                }
            }
        }
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

const vector<Projectile>& Jeu::getProjectilesAllies() const {
    return projectilesAllies;
}

const vector<Projectile>& Jeu::getProjectilesEnnemis() const {
    return projectilesEnnemis;
}

const vector<Amelioration>& Jeu::getChoixAmeliorations() const {
    return choixAmeliorations;
}

const vector<Aura>& Jeu::getAuras() const {
    return auras;
}

bool Jeu::estEnChoixAmelioration() const {
    return enChoixAmelioration;
}

int Jeu::getNiveauActuel() const {
    return vague.getNiveau();
}

int Jeu::getNumeroVague() const {
    return vague.getNumero();
}

int Jeu::getLargeurCarte() const {
    return largeurCarte;
}

int Jeu::getHauteurCarte() const {
    return hauteurCarte;
}

int Jeu::getNiveauAuraJoueur() const {
    return niveauAuraJoueur;
}

int Jeu::getNombreEnnemisRestants() const {
    return ennemis.size();
}