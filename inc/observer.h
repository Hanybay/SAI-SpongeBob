/* 
* Module : observer
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 16/05/2023
*/

#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "types.h"
#include "transformation.h"

// Constantes
#define DEFAULT_FORWARD_MOVE { 0, 0, DEFAULT_MOVE_STEP }
#define DEFAULT_BACK_MOVE { 0, 0, -DEFAULT_MOVE_STEP }
#define DEFAULT_RIGHT_MOVE { -DEFAULT_MOVE_STEP, 0, 0 }
#define DEFAULT_LEFT_MOVE { DEFAULT_MOVE_STEP, 0, 0 }
#define DEFAULT_OBSERVER_RADIUS 0.3f

// Types
// Observateur
typedef struct {
    t_point position;
    float radius;
} t_observer;


// Prototypes des fonctions
// Initialise l'observateur
void init_observer(t_point position);
// Déplace l'observateur vers l'avant
void move_forward();
// Déplace l'observateur vers l'arrière
void move_back();
// Déplace l'observateur vers la gauche
void move_left();
// Déplace l'observateur vers la droite
void move_right();
// Applique une rotation aux vecteurs de déplacement
void rotate_movement_vectors(float vertical_angle, float horizontal_angle);
// Met à jour la caméra
void update_camera(float camera_horizontal_angle, float camera_vertical_angle, float camera_distance);

#endif
