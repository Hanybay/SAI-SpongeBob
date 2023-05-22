/* 
* Module : houses
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 21/05/2023
*/

#include "intersection.h"
#include "drawing.h"
#include "random.h"
#include "house.h"
  
// Variables globales
// // Maisons
t_house houses[MAX_HOUSES];
int houses_count = 0;


// Vérifie si la position n'est pas occupée par une autre maison
int check_house(t_house house) {
    // On vérifie si la maison ne se croise pas avec une autre
    for (int i = 0; i < houses_count; i++)
        // Intersection ?
        if (is_houses_colliding(house, houses[i]))
            return 0;

    return 1;
}

// Ajoute une maison
int add_house(t_point position) {
    t_house house;

    // Nombre de maisons max
    if (houses_count > MAX_HOUSES) return 1;

    // Initialisation de la maison
    house.position = position;
    house.width = DEFAULT_HOUSE_WIDTH;
    house.depth = DEFAULT_HOUSE_DEPTH;
    house.body_height = DEFAULT_HOUSE_BODY_HEIGHT;
    house.roof_height = DEFAULT_HOUSE_ROOF_HEIGHT;
    // // Couleurs
    INIT_COLOR(house.body_color, 132 / 255.0f, 46 / 255.0f, 27 / 255.0f);
    INIT_COLOR(house.roof_color, 80 / 255.0f, 80 / 255.0f, 80 / 255.0f);
    INIT_COLOR(house.door_color, 125 / 255.0f, 66 / 255.0f, 54 / 255.0f);
    INIT_COLOR(house.window_color, 133 / 255.0f, 147 / 255.0f, 192 / 255.0f);

    // Vérification de la position
    if (!check_house(house)) return 0;

    // Ajout
    houses[houses_count++] = house;

    return 1;
}


// Dessine une maison
void draw_house(t_house house) {
    // Coins min, max du corps de la maison
    t_point body_corner1 = {
        house.position.x - house.width / 2, house.position.y, house.position.z - house.depth / 2
    }, body_corner2 = {
        house.position.x + house.width / 2, house.position.y + house.body_height, house.position.z + house.depth / 2
    };

    // Corps de la maison
    draw_house_cube(body_corner1, body_corner2, house.body_color, house.door_color, house.window_color);

    // Dessiner le toit de la maison
    t_point roof_position = { house.position.x, house.position.y + house.body_height + house.roof_height / 2.0f, house.position.z };
    draw_triangular_prism(roof_position, house.width, house.roof_height, house.depth, house.roof_color);
}

// Dessine toutes les maisons
void draw_houses() {
    for (int i = 0; i < houses_count; i++)
        draw_house(houses[i]);
}

// Génère aléatoirement des maisons dans la zone située entre min et max
void generate_random_houses(int count, t_point min, t_point max) {
    for (int i = 0; i < count && i < MAX_HOUSES; i++)
        while (!add_house(random_point(min, max)));
}