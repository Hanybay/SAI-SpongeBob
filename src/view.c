/* 
* Module : view
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 16/05/2023
*/

#include "view.h"
#include <stdio.h>

// Variables globales
// // Déplacements de l'observateur
t_vector front = DEFAULT_FRONT_MOVE,
         back = DEFAULT_BACK_MOVE,
         right = DEFAULT_RIGHT_MOVE,
         left = DEFAULT_LEFT_MOVE;
extern t_point eye_position, target_position;


// Déplace l'observateur vers l'avant
void move_front() {
    eye_position = translate_point(eye_position, front);
    target_position = translate_point(target_position, front);
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
