/* 
* Module : random
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 23/05/2023
*/

#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "types.h"


// Prototypes des fonctions
// Retourne un réel aléatoire dans l'intervalle
float random_float(float min, float max);
// Retourne un entier aléatoire dans l'intervalle
int random_int(int min, int max);
// Retourne un point aléatoire dans l'intervalle
t_point random_point(t_point min, t_point max);

#endif
