/* 
* Module : houses
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 21/05/2023
*/

#ifndef _HOUSES_H_
#define _HOUSES_H_

#include "types.h"

// Constantes
#define MAX_HOUSES 10
#define DEFAULT_HOUSE_WIDTH 2.0f
#define DEFAULT_HOUSE_DEPTH 2.0f
#define DEFAULT_HOUSE_BODY_HEIGHT 1.5f
#define DEFAULT_HOUSE_ROOF_HEIGHT 0.35f

// Types

// // Maison
typedef struct {
    t_point position;
    float width, depth;
    float body_height, roof_height;
    t_color body_color, roof_color, window_color, door_color;
} t_house;


// Prototypes des fonctions
// Ajoute une maison
int add_house(t_point position);
// Vérifie si la position n'est pas occupée par une autre maison
int check_house(t_house house);
// Dessine une maison
void draw_house(t_house house);
// Dessine toutes les maisons
void draw_houses();
// Génère aléatoirement des maisons dans la zone située entre min et max
void generate_random_houses(int count, t_point min, t_point max);

#endif
