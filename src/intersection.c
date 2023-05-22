/* 
* Module : intersection
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 21/05/2023
*/

#include "intersection.h"

// Vérifie si deux AABB s'intersectent
int is_colliding(t_AABB box1, t_AABB box2) {
    // Si l'un des coins de la boîte 1 est à l'extérieur de la boîte 2
    if (box1.max_x < box2.min_x || box1.min_x > box2.max_x) return 0;
    if (box1.max_y < box2.min_y || box1.min_y > box2.max_y) return 0;
    if (box1.max_z < box2.min_z || box1.min_z > box2.max_z) return 0;

    // Si aucune des conditions ci-dessus n'est vraie, alors il y a une intersection
    return 1;
}

// Génère l'AABB de la maison
t_AABB generate_house_AABB(t_house house) {
    t_AABB aabb;

    aabb.min_x = house.position.x - house.width / 2.0f;
    aabb.max_x = house.position.x + house.width / 2.0f;
    aabb.min_y = house.position.y;
    aabb.max_y = house.position.y + house.body_height + house.roof_height; // + Sommet du toit
    aabb.min_z = house.position.z - house.depth / 2.0f;
    aabb.max_z = house.position.z + house.depth / 2.0f;

    return aabb;
}

// Génère l'AABB de l'arbre
t_AABB generate_tree_AABB(t_tree tree) {
    t_AABB aabb;

    aabb.min_x = tree.position.x - tree.trunk_radius;
    aabb.max_x = tree.position.x + tree.trunk_radius;
    aabb.min_y = tree.position.y;
    aabb.max_y = tree.position.y + tree.trunk_height + tree.top_y;  // + Sommet du feuillage
    aabb.min_z = tree.position.z - tree.trunk_radius;
    aabb.max_z = tree.position.z + tree.trunk_radius;

    return aabb;
}

// Vérifie si deux maisons s'intersectent
int is_houses_colliding(t_house house1, t_house house2) {
    t_AABB AABB1 = generate_house_AABB(house1),
           AABB2 = generate_house_AABB(house2);

    return is_colliding(AABB1, AABB2);
}

// Vérifie si deux arbres s'intersectent
int is_trees_colliding(t_tree tree1, t_tree tree2) {
    t_AABB AABB1 = generate_tree_AABB(tree1),
           AABB2 = generate_tree_AABB(tree2);

    return is_colliding(AABB1, AABB2);
}

// Vérifie si un arbre et une maison s'intersectent
int is_tree_house_colliding(t_tree tree, t_house house) {
    t_AABB tree_AABB = generate_tree_AABB(tree),
           house_AABB = generate_house_AABB(house);

    return is_colliding(tree_AABB, house_AABB);
}