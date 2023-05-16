/* 
* Module : view
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 16/05/2023
*/

#ifndef _VIEW_H_
#define _VIEW_H_

#include "types.h"
#include "transformations.h"

// Constantes
#define DEFAULT_FRONT_MOVE { 0, 0, -DEFAULT_MOVE_STEP }
#define DEFAULT_BACK_MOVE { 0, 0, DEFAULT_MOVE_STEP }
#define DEFAULT_RIGHT_MOVE { DEFAULT_MOVE_STEP, 0, 0 }
#define DEFAULT_LEFT_MOVE { -DEFAULT_MOVE_STEP, 0, 0 }

// Prototypes des fonctions
// Déplace l'observateur vers l'avant
void move_front();
// Déplace l'observateur vers l'arrière
void move_back();
// Déplace l'observateur vers la gauche
void move_left();
// Déplace l'observateur vers la droite
void move_right();

#endif
