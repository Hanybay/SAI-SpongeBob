/* 
* Module : matrix
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 29/03/2023
*/

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdarg.h>

// Types
// Matrice
typedef struct {
    // (dim[0] -> nb_lignes, dim[1] -> nb_colonnes)
    int dimensions[2];
    float **values;
} t_matrix;


// Prototypes des fonctions
// Retourne une matrice vide
t_matrix empty_matrix();
// Retourne une matrice vide initialisée avec des zéros 
t_matrix zero_matrix();
// Affiche la matrice donnée
void print_matrix(t_matrix matrix);
// Retourne une copie de la matrice
t_matrix copy_matrix(t_matrix src);
// Retourne la somme des matrices données
t_matrix sum_matrices(int nb_matrices, t_matrix first_operand, ...);
// Retourne la multiplication de deux matrices
t_matrix mult_matrix(t_matrix operand_left, t_matrix operand_right);
// Retourne le produit des matrices
t_matrix product_matrices(int nb_matrices, t_matrix first_operand, ...);
#endif
