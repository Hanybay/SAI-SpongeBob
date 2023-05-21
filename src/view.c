/* 
* Module : view
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 16/05/2023
*/

#include "view.h"
#include <stdio.h>
#include <math.h>
#include <GL/glu.h>

// Variables globales
// // Déplacements de l'observateur
t_vector forward = DEFAULT_FORWARD_MOVE,
         back = DEFAULT_BACK_MOVE,
         right = DEFAULT_RIGHT_MOVE,
         left = DEFAULT_LEFT_MOVE;
extern t_point camera_position;
extern t_point camera_target;


// Déplace l'observateur vers l'avant
void move_forward() {
    camera_position = translate_point(camera_position, forward);
}

// Déplace l'observateur vers l'arrière
void move_back() {
    camera_position = translate_point(camera_position, back);
}

// Déplace l'observateur vers la gauche
void move_left() {
    camera_position = translate_point(camera_position, left);
}

// Déplace l'observateur vers la droite
void move_right() {
    camera_position = translate_point(camera_position, right);
}

// Applique une rotation aux vecteurs de déplacement
void rotate_movement_vectors(float vertical_angle, float horizontal_angle) {
    const t_vector default_forward = DEFAULT_FORWARD_MOVE,
                   default_left = DEFAULT_LEFT_MOVE;
    float horizontal_angle_radians;

    // Conversion des angles en radian
    printf("\n-----------\nangle = %f\n\n", horizontal_angle);
    horizontal_angle_radians = -horizontal_angle * (M_PI  / 360);

    // Rotation par rapport à l'angle horizontal (autour de l'axe y)
    forward = rotate_y_point(default_forward, horizontal_angle_radians);
    left = rotate_y_point(default_left, horizontal_angle_radians);

    // Mise à jour des vecteurs gauche et droit
    back.x = -forward.x;
    back.y = -forward.y;
    back.z = -forward.z;

    right.x = -left.x;
    right.y = -left.y;
    right.z = -left.z;

    PRINT_POINT(forward);
}

// Met à jour la caméra
void update_camera(float camera_horizontal_angle, float camera_vertical_angle, float camera_distance) {
    camera_target.x = sin(camera_horizontal_angle * M_PI / 360.0f) * camera_distance + camera_position.x;
    camera_target.y = sin(camera_vertical_angle * M_PI / 180.0f) * camera_distance + camera_position.y;
    camera_target.z = cos(camera_horizontal_angle * M_PI / 360.0f) * camera_distance + camera_position.z;

    gluLookAt(// Position de la caméra
              camera_position.x, camera_position.y, camera_position.z,
              // Point vers lequel la caméra regarde
              camera_target.x, camera_target.y, camera_target.z,
              // Direction "vers le haut" de la caméra
              0.0f, 1.0f, 0.0f);
}