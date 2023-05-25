/* 
* Module : observer
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 16/05/2023
*/

#include "tree.h"
#include "house.h"
#include "sphere.h"
#include "interaction.h"
#include "observer.h"

// Variables globales
// // Observateur
t_observer observer;
// // Déplacements de l'observateur
t_vector forward = DEFAULT_FORWARD_MOVE,
         back = DEFAULT_BACK_MOVE,
         right = DEFAULT_RIGHT_MOVE,
         left = DEFAULT_LEFT_MOVE;
extern t_point camera_position;
extern t_point camera_target;

// Initialise l'observateur
void init_observer(t_point position) {
    observer.position = position;
    observer.radius = DEFAULT_OBSERVER_RADIUS;
}

// Vérifie la position de l'observateur
int check_observer_position(t_observer observer) {
    // hors-scène
    if (!is_observer_inside(observer)) return 1;

    // Maisons
    if (check_observer_collision_houses(observer)) return 1;

    // Arbres
    if (check_observer_collision_trees(observer)) return 1;

    return 0;
} 

// Déplace l'observateur vers l'avant
void move_forward() {
    t_point tmp_camera_position = translate_point(camera_position, forward);
    t_observer tmp_observer = {
        tmp_camera_position, DEFAULT_OBSERVER_RADIUS
    };

    // Vérifications
    if (check_observer_position(tmp_observer)) return;

    camera_position = tmp_camera_position;
    observer.position = camera_position;
}

// Déplace l'observateur vers l'arrière
void move_back() {
    t_point tmp_camera_position = translate_point(camera_position, back);
    t_observer tmp_observer = {
        tmp_camera_position, DEFAULT_OBSERVER_RADIUS
    };
    
    // Vérifications
    if (check_observer_position(tmp_observer)) return;

    camera_position = tmp_camera_position;
    observer.position = camera_position;
}

// Déplace l'observateur vers la gauche
void move_left() {
    t_point tmp_camera_position = translate_point(camera_position, left);
    t_observer tmp_observer = {
        tmp_camera_position, DEFAULT_OBSERVER_RADIUS
    };
    
    // Vérifications
    if (check_observer_position(tmp_observer)) return;

    camera_position = tmp_camera_position;
    observer.position = camera_position;
}

// Déplace l'observateur vers la droite
void move_right() {
    t_point tmp_camera_position = translate_point(camera_position, right);
    t_observer tmp_observer = {
        tmp_camera_position, DEFAULT_OBSERVER_RADIUS
    };
    
    // Vérifications
    if (check_observer_position(tmp_observer)) return;

    camera_position = tmp_camera_position;
    observer.position = camera_position;
}

// Applique une rotation aux vecteurs de déplacement
void rotate_movement_vectors(float vertical_angle, float horizontal_angle) {
    const t_vector default_forward = DEFAULT_FORWARD_MOVE,
                   default_left = DEFAULT_LEFT_MOVE;
    float horizontal_angle_radians;

    // Conversion des angles en radians
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

// Ouvre une porte si l'observateur est près d'une porte
void try_open_close_door() {
    // Cherche une porte
    int house_number = check_observer_collision_doors(observer);

    // Ouverture / Fermeture de la porte de la maison
    if (house_number != -1)
        open_close_door(house_number);
}