#include <stdio.h>
#include <math.h>
#include "GL/glu.h"
#include "GL/glut.h"
#include "transformations.h"

// Variables globales



// Retourne une matrice carrée vide initialisée avec des zéros
GLfloat *empty_matrix(int size) {
    // Création de la matrice
    GLfloat *matrix = (GLfloat *)malloc(16 * sizeof(GLfloat));
    if (matrix == NULL) {
        fprintf(stderr, "- Erreur -> *empty_matrix(int size) : "
            "échec de l'allocation de mémoire à <matrix> !\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation
    for (int i = 0; i < size; i++)
        matrix[i] = 0.0f;

    return matrix;
}

// Retourne la matrice de translation (tx, ty, tz)
GLfloat *translation_matrix(float tx, float ty, float tz) {
    // Création de la matrice
    GLfloat *matrix = empty_matrix(16);

    // Initialisation
    matrix[0] = 1.0f;
    matrix[5] = 1.0f;
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;

    // Affectation des valeurs de translation
    matrix[3] = tx;
    matrix[7] = ty;
    matrix[11] = tz;

    return matrix;
}

// Retourne la matrice de mise à l'échelle (sx, sy, sz)
GLfloat *scaling_matrix(float sx, float sy, float sz) {
    // Création de la matrice
    GLfloat *matrix = empty_matrix(16);

    // Initialisation
    matrix[15] = 1.0f;

    // Affectation des valeurs de mise à l'échelle
    matrix[0] = sx;
    matrix[5] = sy;
    matrix[10] = sz;

    return matrix;
}

// Retourne la matrice de rotation d'angle (rt) autour de l'axe des x
GLfloat *rotation_x_matrix(float rt) {
    // Création de la matrice
    GLfloat *matrix = empty_matrix(16);

    // Initialisation
    matrix[0] = 1.0f;
    matrix[15] = 1.0f;

    // Affectation des valeurs de rotation
    matrix[5] = cos(rt);
    matrix[6] = -sin(rt);
    matrix[9] = sin(rt);
    matrix[10] = cos(rt);

    return matrix;
}

// Retourne la matrice de rotation d'angle (rt) autour de l'axe des y
GLfloat *rotation_y_matrix(float rt) {
    // Création de la matrice
    GLfloat *matrix = empty_matrix(16);

    // Initialisation
    matrix[5] = 1.0f;
    matrix[15] = 1.0f;

    // Affectation des valeurs de rotation
    matrix[0] = cos(rt);
    matrix[2] = -sin(rt);
    matrix[8] = sin(rt);
    matrix[10] = cos(rt);

    return matrix;
}

// Retourne la matrice de rotation d'angle (rt) autour de l'axe des z
GLfloat *rotation_z_matrix(float rt) {
    // Création de la matrice
    GLfloat *matrix = empty_matrix(16);

    // Initialisation
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;

    // Affectation des valeurs de rotation
    matrix[0] = cos(rt);
    matrix[1] = -sin(rt);
    matrix[4] = sin(rt);
    matrix[5] = cos(rt);

    return matrix;
}

// Affiche la matrice donnée
void print_matrix(GLfloat *matrix, int size, int nb_lines) {
    int line_size = size / nb_lines;

    for (int i = 0; i < size; i++) {
        printf("%6.2f\t", matrix[i]);

        // Saut de ligne pour faire un affichage lisible
        if ((i + 1) % line_size == 0)
            printf("\n");
    }
}