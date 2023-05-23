/* 
* Module : Sphere
* Type : fichier source
* Auteur : BAYAZID Hany
* Date de création : 21/05/2023
*/

#include <math.h>
#include "drawing.h"
#include "sphere.h"

// Variables globales
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

/*void speciesCollisions() {
    for (int i = 0; i < spheres_counter; i++) {
        for (int j = i + 1; j < spheres_counter; j++) {
            float dx = spheres[i].position.x - spheres[j].position.x;
            float dy = spheres[i].position.y - spheres[j].position.y;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance < (spheres[i].radius + spheres[j].radius)) {
                addSpecie((t_color) SPPONGEPAT_SPHERE_COLOR);
            }
        }
    }
}*/


void speciesCollisions() {
    for (int i = 0; i < spheres_counter; i++) {
        for (int j = i + 1; j < spheres_counter; j++) {
            float dx = spheres[i].position.x - spheres[j].position.x;
            float dy = spheres[i].position.y - spheres[j].position.y;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance < (spheres[i].radius + spheres[j].radius)) {
                // Calcule du vecteur directeur de la collision
                float collision_dx = spheres[i].position.x - spheres[j].position.x;
                float collision_dy = spheres[i].position.y - spheres[j].position.y;


                // Normalisation du vecteur directeur (le rendre de longueur 1)
                float collisionVector = sqrt(collision_dx * collision_dx + collision_dy * collision_dy);
                if(collisionVector != 0){
                    collision_dx /= collisionVector;
                    collision_dy /= collisionVector;
                        // Modification de la vitesse des sphères pour qu'elles se déplacent dans la direction opposée
                    float pushPower = 2.0f;
                
                    spheres[i].speed.x = collision_dx * pushPower;
                    //spheres[i].speed.y = collision_dy * pushPower;
                    spheres[j].speed.x = -collision_dx * pushPower;
                    //spheres[j].speed.y = -collision_dy * pushPower;

                }
                else{
                    spheres[i].position.x += 0.01f * (rand() % 100 - 50);
                    spheres[i].position.y += 0.01f * (rand() % 100 - 50);
                }
                if(spheres_counter < MAX_SPHERES){
                    addSpecie((t_color) SPPONGEPAT_SPHERE_COLOR);
                }
                
            }
        }
    }
}




void addSpecie(t_color couleur){
    if(spheres_counter >= MAX_SPHERES){
        fprintf(stderr,"Numéro maximum d'éspèces atteint\n");
        return;
    }
    t_sphere * s = &spheres[spheres_counter];
    
    // On crée l'espèce à l'origine (pour l'instant)
    s->position = (t_point) {0, 0, 0};
    
    s->speed = (t_point) {1, 0, 0};
    
    s->colour = couleur;

    s->radius = DEFAULT_SPHERE_RADIUS;

    s->previousSpeed = s->speed;
    
    spheres_counter+=1;
    printf("NB SPHERE = %d\n",spheres_counter);
}


void moveSpecie(t_sphere *s){
    s->position.x += s->speed.x / 100;
    s->position.y += s->speed.y;
    s->position.z += s->speed.z;


    if (s->speed.x > s->previousSpeed.x) {
        s->speed.x -= 0.001;
        if (s->speed.x < s->previousSpeed.x) {
            s->speed.x = s->previousSpeed.x;
        }
    }
    if (s->speed.y > s->previousSpeed.y) {
        s->speed.y -= 0.01;
        if (s->speed.y < s->previousSpeed.y) {
            s->speed.y = s->previousSpeed.y;
        }
    }
}


void updateSpherePosition(){
    for(int i=0; i<spheres_counter;i++){
        moveSpecie(&spheres[i]);
    } 
}

void drawSpecies(){

    for (int i = 0; i<spheres_counter; i++) {
        t_sphere *s = &spheres[i];
    
<<<<<<< HEAD
        drawSphere(s->position, DEFAULT_SPHERE_RADIUS, s->colour);
        printf("Je dessine la sphère n°%d et sa position est x = %f y = %f z = %f\n",i,s->position.x,s->position.y,s->position.z);
        
=======
        draw_sphere(s->position, DEFAULT_SPHERE_RADIUS, (t_color)DEFAULT_SPHERE_COLOR);
>>>>>>> dev
    }
}
