/* 
* Module : intersection
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 21/05/2023
*/

#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "types.h"


// Prototypes des fonctions
// Vérifie si deux cubes s'intersectent
int check_cube_intersection(t_point cube1_min, t_point cube1_max, t_point cube2_min, t_point cube2_max);

#endif
