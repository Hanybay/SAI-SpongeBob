/* 
* Module : transformations
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 29/03/2023
*/

#include <stdio.h>
#include <math.h>
#include "transformations.h"

// Variables globales
int transformation_matrix_dimensions[2] = { 4, 4 };


// Retourne la matrice de translation (tx, ty, tz)
t_matrix translation_matrix(float tx, float ty, float tz) {
    // Création de la matrice
    t_matrix matrix = zero_matrix(transformation_matrix_dimensions);

    // Initialisation
    matrix.values[0][0] = 1.0f;
    matrix.values[1][1] = 1.0f;
    matrix.values[2][2] = 1.0f;
    matrix.values[3][3] = 1.0f;

    // Affectation des valeurs de translation
    matrix.values[0][3] = tx;
    matrix.values[1][3] = ty;
    matrix.values[2][3] = tz;

    return matrix;
}

// Retourne la matrice de mise à l'échelle (sx, sy, sz)
t_matrix scaling_matrix(float sx, float sy, float sz) {
    // Création de la matrice
    t_matrix matrix = zero_matrix(transformation_matrix_dimensions);

    // Initialisation
    matrix.values[3][3] = 1.0f;

    // Affectation des valeurs de mise à l'échelle
    matrix.values[0][0] = sx;
    matrix.values[1][1] = sy;
    matrix.values[2][2] = sz;

    return matrix;
}

// Retourne la matrice de rotation d'angle (rt) autour de l'axe des x
t_matrix rotation_x_matrix(float rt) {
    // Création de la matrice
    t_matrix matrix = zero_matrix(transformation_matrix_dimensions);

    // Initialisation
    matrix.values[0][0] = 1.0f;
    matrix.values[3][3] = 1.0f;

    // Affectation des valeurs de rotation
    matrix.values[1][1] = cos(rt);
    matrix.values[1][2] = -sin(rt);
    matrix.values[2][1] = sin(rt);
    matrix.values[2][2] = cos(rt);

    return matrix;
}

// Retourne la matrice de rotation d'angle (rt) autour de l'axe des y
t_matrix rotation_y_matrix(float rt) {
    // Création de la matrice
    t_matrix matrix = zero_matrix(transformation_matrix_dimensions);

    // Initialisation
    matrix.values[1][1] = 1.0f;
    matrix.values[3][3] = 1.0f;

    // Affectation des valeurs de rotation
    matrix.values[0][0] = cos(rt);
    matrix.values[0][2] = -sin(rt);
    matrix.values[2][0] = sin(rt);
    matrix.values[2][2] = cos(rt);

    return matrix;
}

// Retourne la matrice de rotation d'angle (rt) autour de l'axe des z
t_matrix rotation_z_matrix(float rt) {
    // Création de la matrice
    t_matrix matrix = zero_matrix(transformation_matrix_dimensions);

    // Initialisation
    matrix.values[2][2] = 1.0f;
    matrix.values[3][3] = 1.0f;

    // Affectation des valeurs de rotation
    matrix.values[0][0] = cos(rt);
    matrix.values[0][1] = -sin(rt);
    matrix.values[1][0] = sin(rt);
    matrix.values[1][1] = cos(rt);

    return matrix;
}

// Retourne l'image d'un point par une translation
t_point translate_point(t_point point, t_vector vector) {
    t_matrix point_representation_matrix = point_matrix(point);
    t_matrix vector_translation_matrix = translation_matrix(vector.x, vector.y, vector.z);
    t_matrix translation_image = product_matrices(1, vector_translation_matrix, point_representation_matrix);

    // Image du point
    t_point image = {
        translation_image.values[0][0],
        translation_image.values[1][0],
        translation_image.values[2][0]
    };

    // Libération de la mémoire allouée
    free_matrix(point_representation_matrix);
    free_matrix(vector_translation_matrix);
    free_matrix(translation_image);

    return image;
}

// Retourne l'image d'un point par une rotation sur l'axe des x
t_point rotate_x_point(t_point point, float angle) {
    t_matrix point_representation_matrix = point_matrix(point);
    t_matrix angle_rotation_matrix = rotation_x_matrix(angle);
    t_matrix rotation_image = product_matrices(1, angle_rotation_matrix, point_representation_matrix);

    // Image du point
    t_point image = {
        rotation_image.values[0][0],
        rotation_image.values[1][0],
        rotation_image.values[2][0]
    };

    // Libération de la mémoire allouée
    free_matrix(point_representation_matrix);
    free_matrix(angle_rotation_matrix);
    free_matrix(rotation_image);

    return image;
}

// Retourne l'image d'un point par une rotation sur l'axe des y
t_point rotate_y_point(t_point point, float angle) {
    t_matrix point_representation_matrix = point_matrix(point);
    t_matrix angle_rotation_matrix = rotation_y_matrix(angle);
    t_matrix rotation_image = product_matrices(1, angle_rotation_matrix, point_representation_matrix);

    // Image du point
    t_point image = {
        rotation_image.values[0][0],
        rotation_image.values[1][0],
        rotation_image.values[2][0]
    };

    // Libération de la mémoire allouée
    free_matrix(point_representation_matrix);
    free_matrix(angle_rotation_matrix);
    free_matrix(rotation_image);

    return image;
}