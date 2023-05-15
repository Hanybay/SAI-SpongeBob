/* 
* Module : matrix
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 29/03/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

// Retourne une matrice vide
t_matrix empty_matrix() {
    t_matrix m = { { 0, 0 }, NULL };
    return m;
}

// Retourne une matrice initialisée avec des zéros
t_matrix zero_matrix(int dimensions[2]) {
    t_matrix matrix;
    // Création de la matrice
    // // Lignes
    matrix.values = (float **)malloc(dimensions[0] * sizeof(float *));
    if (matrix.values == NULL) {
        fprintf(stderr, "- Erreur -> zero_matrix(int dimensions[2]) : "
            "échec de l'allocation de mémoire à <matrix> !\n");
        exit(EXIT_FAILURE);
    }

    // // Colonnes
    for (int i = 0; i < dimensions[0]; i++) {
        matrix.values[i] = (float *)malloc(dimensions[0] * sizeof(float));
        if (matrix.values[i] == NULL) {
            fprintf(stderr, "- Erreur -> zero_matrix(int dimensions[2]) : "
                "échec de l'allocation de mémoire à <matrix[%d]> !\n", i);
            exit(EXIT_FAILURE);
        }
    }
    
    // // Dimensions
    matrix.dimensions[0] = dimensions[0];
    matrix.dimensions[1] = dimensions[1];

    // Initialisation
    for (int i = 0; i < dimensions[0]; i++)
        for (int j = 0; j < dimensions[1]; j++)
            matrix.values[i][j] = 0.0f;

    return matrix;
}

// Vérifie si la matrice est vide
int is_empty_matrix(t_matrix matrix) {
    int is_null, is_size_zero;
    
    is_null = matrix.values == empty_matrix().values;
    is_size_zero = matrix.dimensions[0] == 0 
        && matrix.dimensions[1] == 0;

    if (is_null && !is_size_zero)
        fprintf(stderr, "Avertissement -> is_empty_matrix(t_matrix matrix) :"
            "  la matrice est vide mais ses dimensions ne sont pas (0, 0) !\n");
    else if (!is_null && is_size_zero)
        fprintf(stderr, "Avertissement -> is_empty_matrix(t_matrix matrix) :"
            "  la matrice est non vide mais ses dimensions sont nulles !\n");

    return is_null;
}

// Affiche la matrice donnée
void print_matrix(t_matrix matrix) {
    // Vérification
    if (is_empty_matrix(matrix)) {
        fprintf(stderr, "Erreur -> print_matrix(t_matrix matrix) :"
            "  la matrice <matrix> est vide !\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < matrix.dimensions[0]; i++) {
        // Parcours de chaque ligne
        for (int j = 0; j < matrix.dimensions[1]; j++)
            printf("%6.2f\t", matrix.values[i][j]);
        
        printf("\n");
    }
}

// Retourne une copie de la matrice
t_matrix copy_matrix(t_matrix src) {
    t_matrix copy;

    // Vérification
    if (is_empty_matrix(src)) {
        fprintf(stderr, "Erreur -> copy_matrix(t_matrix src) :"
            "  la matrice <src> est vide !\n");
        exit(EXIT_FAILURE);
    }

    copy = zero_matrix(src.dimensions);
    for (int i = 0; i < src.dimensions[0]; i++)
        memcpy(copy.values[i], src.values[i], src.dimensions[1] * sizeof(float));

    return copy;
}

// Libère la mémoire allouée à la matrice
void free_matrix(t_matrix matrix) {
    // Mémoire
    for (int i = 0; i < matrix.dimensions[0]; i++)
        free(matrix.values[i]);
    free(matrix.values);

    // Dimensions
    matrix.dimensions[0] = 0;
    matrix.dimensions[1] = 0;
}

// Retourne la somme des matrices données
t_matrix sum_matrices(int nb_matrices, t_matrix first_operand, ...) {
    va_list operands;
    t_matrix sum = copy_matrix(first_operand);

    // Vérification des arguments
    if (nb_matrices < 1) {
        fprintf(stderr, "- Erreur -> sum_matrices(int nb_matrices, t_matrix first_operand, ...) :"
            "  il faut au moins une matrice à ajouter !\n");
        exit(EXIT_FAILURE);
    }
    
    if (is_empty_matrix(first_operand)) {
        fprintf(stderr, "- Erreur -> sum_matrices(int nb_matrices, t_matrix first_operand, ...) :"
            "  la matrice <first_operand> est vide !\n");
        exit(EXIT_FAILURE);
    }

    // Somme
    va_start(operands, first_operand);
    for (int i = 0; i < nb_matrices; i++) {
        t_matrix operand = va_arg(operands, t_matrix);

        // Vérification
        if (is_empty_matrix(operand)) {
            fprintf(stderr, "- Erreur -> sum_matrices(int nb_matrices, t_matrix first_operand, ...) :"
                "  la matrice opérande <%d> est vide !\n", i);
            exit(EXIT_FAILURE);
        }
        if (operand.dimensions[0] != first_operand.dimensions[0] ||
            operand.dimensions[1] != first_operand.dimensions[1]) {
            fprintf(stderr, "- Erreur -> sum_matrices(int nb_matrices, t_matrix first_operand, ...) :"
                "  les dimensions de la matrice opérande <%d> diffèrent !\n", i);
            exit(EXIT_FAILURE);
        }

        // Addition
        for (int i = 0; i < operand.dimensions[0]; i++)
            for (int j = 0; j < operand.dimensions[1]; j++)
                sum.values[i][j] += operand.values[i][j];
    }
    va_end(operands);

    return sum;
}


// Retourne la multiplication de deux matrices
t_matrix mult_matrix(t_matrix operand_left, t_matrix operand_right) {
    t_matrix res;
    int dimensions[2];

    // Vérification
    if (is_empty_matrix(operand_right) || is_empty_matrix(operand_left)) {
        fprintf(stderr, "- Erreur -> mult_matrix(t_matrix operand_left, t_matrix operand_right) :"
            "  l'une des deux matrices au moins est vide !\n");
        exit(EXIT_FAILURE);
    }
    // Colonnes == lignes ?
    if (!operand_left.dimensions[1] != !operand_right.dimensions[0]) {
        fprintf(stderr, "- Erreur -> mult_matrix(t_matrix operand_left, t_matrix operand_right) :"
            "  le nombre de colonnes de la matrice opérande gauche (%d) différent du nombre\n"
            "  de lignes de la matrice opérande droite (%d) !\n", operand_left.dimensions[1],
            operand_right.dimensions[0]);
        exit(EXIT_FAILURE);
    }

    // Création de la matrice résultat
    dimensions[0] = operand_left.dimensions[0];
    dimensions[1] = operand_right.dimensions[1];
    res = zero_matrix(dimensions);

    // Multiplication
    for (int i = 0; i < operand_left.dimensions[0]; i++) {
        for (int j = 0; j < operand_right.dimensions[1]; j++) {
            float acc = 0;
            for (int k = 0; k < operand_left.dimensions[1]; k++)
                acc += operand_left.values[i][k] * operand_right.values[k][j];
            res.values[i][j] = acc;
        }
    }

    return res;
}

// Retourne le produit des matrices
t_matrix product_matrices(int nb_matrices, t_matrix first_operand, ...) {
    va_list operands;
    t_matrix operand_right, operand_left;

    // Vérification des arguments
    if (nb_matrices < 1) {
        fprintf(stderr, "- Erreur -> sum_matrices(int nb_matrices, t_matrix first_operand, ...) :"
            "  il faut au moins une matrice à ajouter !\n");
        exit(EXIT_FAILURE);
    }
    
    if (is_empty_matrix(first_operand)) {
        fprintf(stderr, "- Erreur -> sum_matrices(int nb_matrices, t_matrix first_operand, ...) :"
            "  la matrice <first_operand> est vide !\n");
        exit(EXIT_FAILURE);
    }

    // Produit
    // // Premier cas
    operand_right = first_operand;
    va_start(operands, first_operand);
    operand_left = va_arg(operands, t_matrix);
    
    // // // Multiplication
    operand_right = mult_matrix(operand_right, operand_left);

    for (int i = 1; i < nb_matrices; i++) {
        operand_left = va_arg(operands, t_matrix);

        // Multiplication des opérandes droite et gauche courantes
        t_matrix tmp = mult_matrix(operand_right, operand_left);
        
        // On libère l'opérande droite et on lui affecte tmp
        free_matrix(operand_right);
        operand_right = tmp;
    }
    va_end(operands);

    return operand_right;
}

