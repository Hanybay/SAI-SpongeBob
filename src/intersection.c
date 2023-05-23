/* 
* Module : intersection
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 21/05/2023
*/

#include "intersection.h"

// Vérifie si les deux AABB s'intersectent
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

// Génère l'AABB de l'être vivant (donc, d'une sphère dans notre cas)
t_AABB generate_being_AABB(t_sphere being) {
    t_AABB aabb;

    aabb.min_x = being.position.x - being.radius;
    aabb.max_x = being.position.x + being.radius;
    aabb.min_y = being.position.y - being.radius;
    aabb.max_y = being.position.y + being.radius;
    aabb.min_z = being.position.z - being.radius;
    aabb.max_z = being.position.z + being.radius;

    return aabb;
}

// Génère l'AABB de la balle
t_AABB generate_bullet_AABB(t_bullet bullet) {
    t_AABB aabb;

    aabb.min_x = bullet.position.x - bullet.radius;
    aabb.max_x = bullet.position.x + bullet.radius;
    aabb.min_y = bullet.position.y - bullet.radius;
    aabb.max_y = bullet.position.y + bullet.radius;
    aabb.min_z = bullet.position.z - bullet.radius;
    aabb.max_z = bullet.position.z + bullet.radius;

    return aabb;   
}

// Génère l'AABB de l'observateur
t_AABB generate_observer_AABB(t_observer observer) {
    t_AABB aabb;

    aabb.min_x = observer.position.x - observer.radius;
    aabb.max_x = observer.position.x + observer.radius;
    aabb.min_y = observer.position.y - observer.radius;
    aabb.max_y = observer.position.y + observer.radius;
    aabb.min_z = observer.position.z - observer.radius;
    aabb.max_z = observer.position.z + observer.radius;

    return aabb;
}

// Génère l'AABB d'une porte de maison
t_AABB generate_door_AABB(t_door door) {
    t_AABB aabb;

    aabb.min_x = door.min_corner.x;
    aabb.max_x = door.max_corner.x;
    aabb.min_y = door.min_corner.y;
    aabb.max_y = door.max_corner.y;
    aabb.min_z = door.min_corner.z;
    aabb.max_z = door.max_corner.z;

    return aabb;
}

// Vérifie si les deux maisons s'intersectent
int is_houses_colliding(t_house house1, t_house house2) {
    t_AABB AABB1 = generate_house_AABB(house1),
           AABB2 = generate_house_AABB(house2);

    return is_colliding(AABB1, AABB2);
}

// Vérifie si les deux arbres s'intersectent
int is_trees_colliding(t_tree tree1, t_tree tree2) {
    t_AABB AABB1 = generate_tree_AABB(tree1),
           AABB2 = generate_tree_AABB(tree2);

    return is_colliding(AABB1, AABB2);
}

// Vérifie si l'arbre et la maison s'intersectent
int is_tree_house_colliding(t_tree tree, t_house house) {
    t_AABB tree_AABB = generate_tree_AABB(tree),
           house_AABB = generate_house_AABB(house);

    return is_colliding(tree_AABB, house_AABB);
}

// Vérifie si l'être vivant et la maison s'intersectent
int is_being_house_colliding(t_sphere being, t_house house) {
    t_AABB being_AABB = generate_being_AABB(being),
           house_AABB = generate_house_AABB(house);

    return is_colliding(being_AABB, house_AABB);
}

// Vérifie si l'être vivant et l'arbre s'intersectent
int is_being_tree_colliding(t_sphere being, t_tree tree) {
    t_AABB being_AABB = generate_being_AABB(being),
           tree_AABB = generate_tree_AABB(tree);

    return is_colliding(being_AABB, tree_AABB);
}

// Vérifie si l'observateur et la maison s'intersectent
int is_observer_house_colliding(t_observer observer, t_house house) {
    t_AABB being_AABB = generate_observer_AABB(observer),
           house_AABB = generate_house_AABB(house);

    return is_colliding(being_AABB, house_AABB);
}

// Vérifie si l'observateur et l'arbre s'intersectent
int is_observer_tree_colliding(t_observer observer, t_tree tree) {
    t_AABB being_AABB = generate_observer_AABB(observer),
           tree_AABB = generate_tree_AABB(tree);

    return is_colliding(being_AABB, tree_AABB);
}

// Vérifie si l'observateur et un être vivant s'intersectent
int is_observer_being_colliding(t_observer observer, t_sphere being) {
    float dx = observer.position.x - being.position.x;
    float dy = observer.position.y - being.position.y;
    float dz = observer.position.z - being.position.z;

    float distance = dx * dx + dy * dy + dz * dz;
    float radiusSum = observer.radius + being.radius;

    return distance <= radiusSum * radiusSum;
}

// Vérifie si l'observateur et la porte s'intersectent
int is_observer_door_colliding(t_observer observer, t_door door) {
    t_AABB being_AABB = generate_observer_AABB(observer),
           door_AABB = generate_door_AABB(door);

    return is_colliding(being_AABB, door_AABB);
}