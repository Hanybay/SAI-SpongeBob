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
#define DEFAULT_FRUSTUM { .left = -4096, .right = 4096, .top = 2048, .bottom = -2048, .near = 102.4, .far = 16384 }
#define DEFAULT_EYE_POSITION { 0, 4096, 4096 }
#define DEFAULT_TARGET_POSITION { 0, 0, 0 }

// Prototypes des fonctions
// Réalise l'affichage
void display();

#endif
