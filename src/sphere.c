/* 
* Module : Sphere
* Type : fichier source
* Auteur : BAYAZID Hany
* Date de création : 21/05/2023
*/

#include <math.h>
#include "drawing.h"
#include "sphere.h"

t_sphere spheres[MAX_SPHERES];
int spheres_counter = 0;



int isSphereCollided(t_sphere s1, t_sphere s2) {
    float dx = s1.position.x - s2.position.x;
    float dy = s1.position.y - s2.position.y;
    float dz = s1.position.z - s2.position.z;

    float distance = dx*dx + dy*dy + dz*dz;
    float radiusSum = s1.radius + s2.radius;

    return distance <= radiusSum * radiusSum;
}


void addSpecie(){
    if(spheres_counter >= MAX_SPHERES){
        fprintf(stderr,"Numéro maximum d'éspèces atteint\n");
        return;
    }
    t_sphere * s = &spheres[spheres_counter];
    
    // On crée l'espèce à l'origine (pour l'instant)
    s->position = (t_point) {0, 0, 0};
    
    s->speed = (t_point) {1, 0, 0};
    
    s->colour = (t_color) DEFAULT_SPHERE_COLOR;

    s->radius = DEFAULT_SPHERE_RADIUS;
    
    spheres_counter++;
}


void moveSpecie(t_sphere *s){
    s->position.x += s->speed.x / 100;
    s->position.y += s->speed.y;
    s->position.z += s->speed.z;
}


void updateSpherePosition(){
    for(int i=0; i<spheres_counter;i++){
        moveSpecie(&spheres[i]);
    }  
}

void drawSpecies(){

    for (int i = 0; i<spheres_counter; i++) {
        t_sphere *s = &spheres[i];
    
        drawSphere(s->position, DEFAULT_SPHERE_RADIUS, (t_color)DEFAULT_SPHERE_COLOR);
    }
}
