#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "GL/gl.h"

// Prototypes des fonctions
// Retourne la matrice de translation (tx, ty, tz)
GLfloat *translation_matrix(float tx, float ty, float tz);
// Retourne la matrice de mise à l'échelle (sx, sy, sz)
GLfloat *scaling_matrix(float sx, float sy, float sz);
// Retourne la matrice de rotation d'angle (rt) autour de l'axe des x
GLfloat *rotation_x_matrix(float rt);
// Retourne la matrice de rotation d'angle (rt) autour de l'axe des y
GLfloat *rotation_y_matrix(float rt);
// Retourne la matrice de rotation d'angle (rt) autour de l'axe des z
GLfloat *rotation_z_matrix(float rt);
// Affiche la matrice donnée
void print_matrix(GLfloat *matrix, int size, int nb_lines);

#endif