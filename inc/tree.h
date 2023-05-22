/* 
* Module : tree
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 22/05/2023
*/

#ifndef _TREE_H_
#define _TREE_H_

#include "types.h"

// Constantes
#define MAX_TREES 150
#define MIN_FOLIAGES 10
#define MAX_FOLIAGE 20
#define TRUNK_RADIUS 0.1f
#define MIN_FOLIAGE_RADIUS 0.1f
#define MAX_FOLIAGE_RADIUS 0.5f
#define DEFAULT_TRUNK_SLICES 32
#define DEFAULT_TRUNK_STACKS 32
#define DEFAULT_TRUNK_HEIGHT 2.0f

// Types

// // Feuillage
typedef struct {
    t_point position;
    float radius;
} t_foliage;

// // Arbre
typedef struct {
    t_point position;
    float trunk_radius;
    float trunk_height;
    float top_y;
    int foliage_count;
    t_foliage foliage[MAX_FOLIAGE];
} t_tree;


// Prototypes des fonctions
// Vérifie si la position de l'arbre est possible par rapport aux autres éléments du décor (arbres et décors)
int check_tree(t_tree tree);
// Ajoute un arbre
int add_tree(t_point position);
// Génère le feuillage de l'arbre
void generate_foliage(t_tree *tree);
// Dessine un arbre
void draw_tree(t_tree tree);
// Dessine tous les arbres
void draw_trees();
// Génère aléatoirement des arbres dans la zone située entre min et max
void generate_random_trees(int count, t_point min, t_point max);

#endif
