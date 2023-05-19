/* 
* Module : drawing
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 18/05/2023
*/

#ifndef _DRAWING_H_
#define _DRAWING_H_

#include "types.h"

// Prototypes des fonctions
// Dessine un plus à la position donnée
void drawPlus(t_point position, float size, t_color color);
// Dessine un plus en 2D à la position donnée (position.z inutile)
void drawPlus2D(t_point position, float size, t_color color);
// Dessine une ligne entre deux points
void drawLine(t_point side1, t_point side2, t_color color);

#endif
