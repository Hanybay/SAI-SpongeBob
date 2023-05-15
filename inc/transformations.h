/* 
* Module : transformations
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 29/03/2023
*/

#ifndef _TRANSFORMATIONS_H_
#define _TRANSFORMATIONS_H_

#include "matrix.h"

// Prototypes des fonctions
// Retourne la matrice de translation (tx, ty, tz)
t_matrix translation_matrix(float tx, float ty, float tz);
// Retourne la matrice de mise à l'échelle (sx, sy, sz)
t_matrix scaling_matrix(float sx, float sy, float sz);
// Retourne la matrice de rotation d'angle (rt) autour de l'axe des x
t_matrix rotation_x_matrix(float rt);
// Retourne la matrice de rotation d'angle (rt) autour de l'axe des y
t_matrix rotation_y_matrix(float rt);
// Retourne la matrice de rotation d'angle (rt) autour de l'axe des z
t_matrix rotation_z_matrix(float rt);

#endif
