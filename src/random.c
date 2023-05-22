/* 
* Module : random
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 23/05/2023
*/

#include "random.h"
  

// Retourne un réel aléatoire dans l'intervalle
float random_float(float min, float max) {
    if (max < min) {
        // Échange min-max
        float temp = max;
        max = min;
        min = temp;
    }
    
    return (float)rand() / RAND_MAX * (max - min) + min;
}

// Retourne un entier aléatoire dans l'intervalle
int random_int(int min, int max) {
    if (max < min) {
        // Échange min-max
        int temp = max;
        max = min;
        min = temp;
    }

    return rand() % (max - min + 1) + min;
}

// Retourne un point aléatoire dans l'intervalle
t_point random_point(t_point min, t_point max) {
    t_point point = {
        random_float(min.x, max.x),
        random_float(min.y, max.y),
        random_float(min.z, max.z),
    };

    return point;
}