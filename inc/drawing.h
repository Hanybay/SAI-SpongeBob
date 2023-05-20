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
void drawPlus(t_point position, float size, t_color color, float line_width);
// Dessine un plus en 2D à la position donnée (position.z inutile)
void drawPlus2D(t_point position, float size, t_color color, float line_width);
// Dessine une ligne entre deux points
void drawLine(t_point corner1, t_point corner2, t_color color, float line_width);
// Dessine un cube
void drawCube(t_point corner1, t_point corner2, t_color color);

#endif
