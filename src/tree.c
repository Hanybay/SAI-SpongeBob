/* 
* Module : tree
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 22/05/2023
*/

#include "drawing.h"
#include "house.h"
#include "interaction.h"
#include "random.h"
#include "tree.h"

// Variables globales
extern t_house houses[MAX_HOUSES];
extern int houses_count;
t_tree trees[MAX_TREES];
int trees_count = 0;


// Vérifie si la position de l'arbre est possible par rapport aux autres éléments du décor (arbres et décors)
int check_tree(t_tree tree) {
    // Par rapport aux autres arbres
    for (int i = 0; i < trees_count; i++)
        // Intersection ?
        if (is_trees_colliding(tree, trees[i]))
            return 0;
    
    // Par rapport aux autres maisons
    for (int i = 0; i < houses_count; i++)
        // Intersection ?
        if (is_tree_house_colliding(tree, houses[i]))
            return 0;

    return 1;
}

// Ajoute un arbre
int add_tree(t_point position) {
    t_tree tree;

    // Nombre max d'arbres
    if (trees_count > MAX_TREES) return 1;

    // Initialisation des variables de l'arbre
    tree.position = position;
    tree.trunk_radius = TRUNK_RADIUS;
    tree.trunk_height = DEFAULT_TRUNK_HEIGHT;
    tree.foliage_count = random_int(MIN_FOLIAGES, MAX_FOLIAGE);
    generate_foliage(&tree);

    // Vérification de l'arbre par rapport aux autres élément du décor
    if (!check_tree(tree)) return 0;

    // Ajout de l'arbre
    trees[trees_count++] = tree;

    return 1;
}

// Génère le feuillage de l'arbre
void generate_foliage(t_tree *tree) {
    float top_foliage_y = 0;

    // Couleurs
    t_color foliage_colors[5] = {
        { 0 / 255.0f, 135 / 255.0f, 62 / 255.0f },
        { 0 / 255.0f, 177 / 255.0f, 64 / 255.0f },
        { 0 / 255.0f, 154 / 255.0f, 23 / 255.0f }
    };

    // Draw the foliage
    for (int i = 0; i < tree->foliage_count; i++) {
        // Offsets aléatoires pour le feuillage
        float offsetX = random_float(-0.5, 0.5);
        float offsetY = random_float(-0.5, 0.5);
        float offsetZ = random_float(-0.5, 0.5);

        // Position du feuillage
        INIT_POINT(tree->foliage[i].position, tree->position.x + offsetX, tree->position.y + tree->trunk_height + offsetY, tree->position.z + offsetZ);

        // Taille aléatoire
        tree->foliage[i].radius = random_float(MIN_FOLIAGE_RADIUS, MAX_FOLIAGE_RADIUS);

        // Couleur du feuillage
        tree->foliage[i].color = foliage_colors[random_int(0, 2)];

        // Sommet de l'arbre
        if (tree->foliage[i].position.y > top_foliage_y)
            top_foliage_y = tree->foliage[i].position.y;
    }

    // Sommet de l'arbre final
    tree->top_y = top_foliage_y;
}

// Dessine un arbre
void draw_tree(t_tree tree) {
    static t_color trunk_color = {
        59.0f / 255, 52.0f / 255, 41.0f / 255
    };

    // Tronc
    draw_cylinder(tree.position, tree.trunk_radius, tree.trunk_height, DEFAULT_TRUNK_SLICES, DEFAULT_TRUNK_STACKS, trunk_color);

    // Feuillage
    for (int i = 0; i < tree.foliage_count; i++)
        draw_sphere(tree.foliage[i].position, tree.foliage[i].radius, tree.foliage[i].color);
}

// Dessine tous les arbres
void draw_trees() {
    for (int i = 0; i < trees_count; i++)
        draw_tree(trees[i]);
}

// Génère aléatoirement des arbres dans la zone située entre min et max
void generate_random_trees(int count, t_point min, t_point max) {
    for (int i = 0; i < count && i < MAX_TREES; i++)
        while (!add_tree(random_point(min, max)));
}

// Teste les collisions entre l'observateur et tous les arbres
int check_observer_collision_trees(t_observer observer) {
    for (int i = 0; i < trees_count; i++) {
        if (is_observer_tree_colliding(observer, trees[i]))
            // Collision
            return 1;
    }

    return 0;
}