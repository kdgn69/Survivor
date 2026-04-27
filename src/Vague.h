/**
 * @file Vague.h
 * Gère la progression des vagues et des niveaux.
 */

/**
 * @class Vague
 * Permet de suivre le numéro de vague et le niveau actuel,
 * et de déterminer combien d’ennemis doivent apparaître.
 */
class Vague {
private:
    int niveau; /**< Niveau actuel du jeu */
    int numero; /**< Numéro de la vague dans le niveau */

public:
    /**
     * Initialise le jeu au niveau 1, vague 1.
     */
    Vague();

    /**
     * Passe à la vague suivante.
     * Si la vague dépasse 6, on passe au niveau suivant.
     */
    void passerSuivante();

    /**
     * Retourne le numéro de la vague actuelle.
     */
    int getNumero() const;

    /**
     * Retourne le niveau actuel.
     */
    int getNiveau() const;

    /**
     * Calcule le nombre d’ennemis à générer pour la vague.
     */
    int getNombreEnnemis() const;
};