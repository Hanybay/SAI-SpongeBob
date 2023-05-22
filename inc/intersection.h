/* 
* Module : intersection
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 21/05/2023
*/

#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "types.h"
#include "house.h"
#include "tree.h"


// Prototypes des fonctions
// Vérifie si deux AABB s'intersectent
int is_colliding(t_AABB box1, t_AABB box2);
// Génère l'AABB de la maison
t_AABB generate_house_AABB(t_house house);
// Génère l'AABB de l'arbre
t_AABB generate_tree_AABB(t_tree tree);
// Vérifie si deux maisons s'intersectent
int is_houses_colliding(t_house house1, t_house house2);
// Vérifie si deux arbres s'intersectent
int is_trees_colliding(t_tree tree1, t_tree tree2);
// Vérifie si un arbre et une maison s'intersectent
int is_tree_house_colliding(t_tree tree, t_house house);

#endif
