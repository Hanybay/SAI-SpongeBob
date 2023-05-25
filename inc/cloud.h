/* 
* Module : cloud
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 25/05/2023
*/

#ifndef _CLOUD_H_
#define _CLOUD_H_

#include "types.h"

// Constantes
#define MAX_CLOUDS 50
#define MIN_GAZ_BALLS 15
#define MAX_GAZ_BALLS 20
#define MIN_GAZ_BALL_RADIUS 3.0f
#define MAX_GAZ_BALL_RADIUS 6.0f
#define DEFAULT_CLOUD_Y 50.0f

// Types

// Boule de gaz
typedef struct {
    t_point position;
    float radius;
    t_color color;
} t_gaz_ball;

// Nuage
typedef struct {
    t_point position;
    t_gaz_ball gaz_balls[MAX_GAZ_BALLS];
    int gaz_balls_count;
} t_cloud;


// Prototypes des fonctions
// Vérifie si la position du nuage est possible par rapport aux autres nuages
int check_cloud(t_cloud cloud);
// Ajoute un nuage
int add_cloud(t_point position);
// Génère les boules de gaz du nuage
void generate_gaz_balls(t_cloud *cloud);
// Dessine un nuage
void draw_cloud(t_cloud cloud);
// Dessine tous les nuages
void draw_clouds();
// Génère aléatoirement des nuages dans la zone située entre min et max
void generate_random_clouds(int count, t_point min, t_point max);
// Déplace le nuage
void move_cloud(t_cloud *cloud, t_vector vector);
// Déplace tous les nuages
void move_clouds(t_vector vector);
// Déplace les nuages
void update_clouds_positions();

#endif
