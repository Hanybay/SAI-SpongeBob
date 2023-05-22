/* 
* Module : bullet
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 20/05/2023
*/

#ifndef _BULLET_H_
#define _BULLET_H_

#include "types.h"

// Constantes
#define MAX_BULLETS 100
#define MAX_BULLET_STEPS 10
#define DEFAULT_BULLET_COLOR { 1.0f, 0.0f, 0.0f }
#define DEFAULT_BULLET_RADIUS 0.01f

// Types

// // Balle
typedef struct {
    t_point position;
    t_point start;
    t_point end;
    float speed;
    int steps;
} t_bullet;


// Prototypes des fonctions
// Tire une balle (rajoute une balle dans le monde)
void shoot_bullet(t_point start, t_point end, float speed);
// Met à jour les positions des balles
void update_bullets_positions();
// Dessine les balles
void draw_bullets();

#endif
