/* 
* Module : Pile
* Type : fichier source
* Auteur : BAYAZID Hany
* Date de création : 25/05/2023
*/

#include <math.h>
#include "interaction.h"
#include "drawing.h"
#include "sphere.h"
#include "random.h"
#include"pile.h"



#define MAX_SPHERES 100

int spheresStack[MAX_SPHERES];
int stackIndex = -1; // indice du sommet de la pile
extern t_sphere spheres[MAX_SPHERES];
extern int spheres_counter;


// Tue l'espèce à l'indice donné
void killSpecie(int index) {
    spheres[index].status = 0;
    // Ajouter l'indice à la pile des indices libres
    spheresStack[++stackIndex] = index;
}

void addSpecieIndex(t_color colour, float radius) {
    if (spheres_counter < MAX_SPHERES) {
        int index;
        // Si la pile n'est pas vide, utiliser un indice libre
        if (stackIndex != -1) {
            index = spheresStack[stackIndex--];
        } else {
            // Sinon, ajouter à la fin du tableau
            index = spheres_counter++;
        }
        // Ajouter la nouvelle espèce à l'indice trouvé
        spheres[index].colour = colour;
        spheres[index].radius = radius;
        spheres[index].status = 1;
    }
}

