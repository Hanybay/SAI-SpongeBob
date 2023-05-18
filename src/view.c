/* 
* Module : view
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 16/05/2023
*/

#include "view.h"
#include <stdio.h>
#include <math.h>

// Variables globales
// // Déplacements de l'observateur
t_vector forward = DEFAULT_FORWARD_MOVE,
         back = DEFAULT_BACK_MOVE,
         right = DEFAULT_RIGHT_MOVE,
         left = DEFAULT_LEFT_MOVE;
extern t_point eye_position, target_position;


// Déplace l'observateur vers l'avant
void move_forward() {
    eye_position = translate_point(eye_position, forward);
    target_position = translate_point(target_position, forward);
}

// Déplace l'observateur vers l'arrière
void move_back() {
    eye_position = translate_point(eye_position, back);
    target_position = translate_point(target_position, back);
}

// Déplace l'observateur vers la gauche
void move_left() {
    eye_position = translate_point(eye_position, left);
    target_position = translate_point(target_position, left);
}

// Déplace l'observateur vers la droite
void move_right() {
    eye_position = translate_point(eye_position, right);
    target_position = translate_point(target_position, right);
}

// Applique une rotation aux vecteurs de déplacement
void rotate_view(float dx, float dy) {
    float mouse_sensitivity = 2 * M_PI / WINDOW_WIDTH;

    // Calcul des angles de rotation liés au lacet et au tangage
    float yaw_angle = dx * mouse_sensitivity;
    // float pitch_angle = dy * mouse_sensitivity;

    print_matrix(point_matrix(forward));
    printf("\n");

    // Rotation par rapport au lacet (axe y)
    forward = rotate_y_point(forward, yaw_angle);
    left = rotate_y_point(left, yaw_angle);

    // Rotation par rapport au tangage (axe x)
    // forward = rotate_x_point(forward, pitch_angle);
    // left = rotate_x_point(left, pitch_angle);

    print_matrix(point_matrix(forward));
    printf("------\n");

    // Mise à jour des vecteurs gauche et droit
    back.x = -forward.x;
    back.y = -forward.y;
    back.z = -forward.z;

    right.x = -left.x;
    right.y = -left.y;
    right.z = -left.z;

    // On déplace la vue
    target_position.x += dx * 5;
    target_position.y += dy * 5;
}