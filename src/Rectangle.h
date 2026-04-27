#ifndef RECTANGLE_H
#define RECTANGLE_H

/**
 * @file Rectangle.h
 * Définit une structure simple pour gérer les collisions.
 */

/**
 * @struct Rectangle
 * Représente une zone rectangulaire avec une position et une taille.
 */
struct Rectangle {
    float x;        /**< Position horizontale */
    float y;        /**< Position verticale */
    float largeur;  /**< Largeur du rectangle */
    float hauteur;  /**< Hauteur du rectangle */
};

/**
 * Vérifie si deux rectangles se chevauchent.
 */
bool collisionRectangles(const Rectangle& a, const Rectangle& b);

/**
 * Vérifie si deux rectangles sont collés (contact sans chevauchement).
 */
bool rectanglesColles(const Rectangle& a, const Rectangle& b);

#endif