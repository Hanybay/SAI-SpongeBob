/* 
* Module : intersection
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 21/05/2023
*/

#include "intersection.h"
  
// Vérifie si deux cubes s'intersectent
int check_cube_intersection(t_point cube1_min, t_point cube1_max, t_point cube2_min, t_point cube2_max) {
    // Si l'un des coins du cube 1 est à l'extérieur du cube 2
    if (cube1_max.x < cube2_min.x || cube1_min.x > cube2_max.x) return 0;
    if (cube1_max.y < cube2_min.y || cube1_min.y > cube2_max.y) return 0;
    if (cube1_max.z < cube2_min.z || cube1_min.z > cube2_max.z) return 0;

    // Si aucune des conditions ci-dessus n'est vraie, alors il y a une intersection
    return 1;
}