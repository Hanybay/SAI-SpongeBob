/* 
* Module : interaction
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 21/05/2023
*/

#ifndef _INTERACTION_H_
#define _INTERACTION_H_

#include "types.h"
#include "house.h"
#include "tree.h"
#include "sphere.h"
#include "bullet.h"
#include "observer.h"


// Prototypes des fonctions
// Vérifie si les deux AABB s'intersectent
int is_colliding(t_AABB box1, t_AABB box2);
// Vérifie si le point est dans l'AABB
int is_inside(t_point point, t_AABB box);
// Réduit l'AABB du nombre de pixels
void shrink_AABB(t_AABB *box, float pixels);
// Génère l'AABB de la maison
t_AABB generate_house_AABB(t_house house);
// Génère l'AABB de l'arbre
t_AABB generate_tree_AABB(t_tree tree);
// Génère l'AABB de l'être vivant (donc, d'une sphère dans notre cas)
t_AABB generate_being_AABB(t_sphere sphere);
// Génère l'AABB de la balle
t_AABB generate_bullet_AABB(t_bullet bullet);
// Génère l'AABB de l'observateur
t_AABB generate_observer_AABB(t_observer observer);
// Génère l'AABB d'une porte de maison
t_AABB generate_door_AABB(t_door door);
// Vérifie si les deux maisons s'intersectent
int is_houses_colliding(t_house house1, t_house house2);
// Vérifie si les deux arbres s'intersectent
int is_trees_colliding(t_tree tree1, t_tree tree2);
// Vérifie si l'arbre et la maison s'intersectent
int is_tree_house_colliding(t_tree tree, t_house house);
// Vérifie si l'être vivant et la maison s'intersectent
int is_being_house_colliding(t_sphere being, t_house house);
// Vérifie si l'être vivant et l'arbre s'intersectent
int is_being_tree_colliding(t_sphere being, t_tree tree);
// Vérifie si l'observateur et la maison s'intersectent
int is_observer_house_colliding(t_observer observer, t_house house);
// Vérifie si l'observateur et l'arbre s'intersectent
int is_observer_tree_colliding(t_observer observer, t_tree tree);
// Vérifie si l'observateur et un être vivant s'intersectent
int is_observer_being_colliding(t_observer observer, t_sphere being);
// Vérifie si l'observateur et la porte s'intersectent
int is_observer_door_colliding(t_observer observer, t_door door);
// Vérifie si l'être vivant est dans la maison
int is_being_inside_house(t_sphere being, t_house house);
// Vérifie si l'observateur est dans la maison
int is_observer_inside_house(t_observer observer, t_house house);
// Vérifie si l'observateur est prêt de la porte
int is_observer_near_door(t_observer observer, t_door door);
// Vérifie si l'observateur peut passer à travers la porte
int can_observer_pass_door(t_observer observer, t_door door);

#endif
