/* 
* Module : display
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 30/03/2023
*/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "types.h"

// Constantes
#define DEFAULT_FRUSTUM { .left = -2048, .right = 2048, .top = 2048, .bottom = -2048, .near = 1024, .far = 4096 }
#define DEFAULT_EYE_POSITION { DEFAULT_DISTANCE, DEFAULT_DISTANCE, DEFAULT_DISTANCE }
#define DEFAULT_TARGET_POSITION { 0, 0, 0 }

// Prototypes des fonctions
// Réalise l'affichage
void display();

#endif
