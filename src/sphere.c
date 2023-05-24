/* 
* Module : Sphere
* Type : fichier source
* Auteur : BAYAZID Hany
* Date de création : 21/05/2023
*/

#include <math.h>
#include "interaction.h"
#include "drawing.h"
#include "sphere.h"
#include "random.h"
#include "intersection.h"

// Variables globales
t_sphere spheres[MAX_SPHERES];
int spheres_counter = 0;
extern t_point platform_min_corner;
extern t_point platform_max_corner;
extern t_house houses[MAX_HOUSES];
extern int houses_count;


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
        for (int j = 0; j < spheres_counter; j++) {
            if (j == i) continue;
            float dx = spheres[i].position.x - spheres[j].position.x;
            float dy = spheres[i].position.y - spheres[j].position.y;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance < (spheres[i].radius + spheres[j].radius)) {
                collisionType(i, j, 1);
            }
        }
        for(int k=0; k < houses_count;k++){
            if(is_being_house_colliding(spheres[i], houses[k])){
                collisionType(i,k,0);
            }
        }
    }
}




void addSpecie(t_color couleur,int choix){
    if(spheres_counter >= MAX_SPHERES){
        fprintf(stderr,"Numéro maximum d'éspèces atteint\n");
        return;
    }
    t_sphere * s = &spheres[spheres_counter];
    
    // On crée l'espèce à l'origine (pour l'instant)

    if(choix == 0){
        s->position = (t_point) {0, 0.5f, 0};
    }
    else{
        s->position = random_point(platform_min_corner,platform_max_corner);
        s->position.z = 0.5f;
    }
    
    s->speed = (t_point) {1, 0, 1};
    
    s->colour = couleur;

    s->radius = DEFAULT_SPHERE_RADIUS;

    s->previousSpeed = s->speed;

    s->collisionTime = COLLISION_DELAY;
    
    spheres_counter+=1;
    printf("NB SPHERE = %d\n",spheres_counter);
}


void moveSpecie(t_sphere *s){
    s->position.x += s->speed.x / 100;
    s->position.y += s->speed.y;
    s->position.z += s->speed.z / 100;


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
    
        draw_sphere(s->position, DEFAULT_SPHERE_RADIUS, s->colour);
        // printf("Je dessine la sphère n°%d et sa position est x = %f y = %f z = %f\n",i,s->position.x,s->position.y,s->position.z);
    }
}


t_color combineColours(t_color c1, t_color c2) {
    t_color res;
    float biais = ((rand() % 100) / 100.0f - 0.5f);
    res.r = (c1.r + c2.r) / 2.0f + biais;
    res.g = (c1.g + c2.g) / 2.0f + biais;
    res.b = (c1.b + c2.b) / 2.0f + biais;


    // Limiter les composantes de couleur entre 0 et 1
    res.r = fmax(fmin(res.r, 1.0f), 0.0f);
    res.g = fmax(fmin(res.g, 1.0f), 0.0f);
    res.b = fmax(fmin(res.b, 1.0f), 0.0f);

    return res;
}

void collisionType(int i, int j, int choix){

    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float collision_dx, collision_dz, collisionVector;
    if (choix == 1){
        collision_dx = spheres[i].position.x - spheres[j].position.x;
        collision_dz = spheres[i].position.z - spheres[j].position.z;
    }
    else{
        collision_dx = spheres[i].position.x - houses[j].position.x;
        collision_dz = spheres[i].position.z - houses[j].position.z;
    }
    // Calcule du vecteur directeur de la collision
    collisionVector = sqrt(collision_dx * collision_dx + collision_dz * collision_dz);
    if (collisionVector != 0){
        collision_dx /= collisionVector;
        collision_dz /= collisionVector;

        // Modification de la vitesse des sphères pour qu'elles se déplacent dans la direction opposée
        float pushPower = 2.0f;

        spheres[i].speed.x = collision_dx * pushPower;
        spheres[i].speed.z = collision_dz * pushPower;
        if (choix == 1){
            spheres[j].speed.x = -collision_dx * pushPower;
            spheres[j].speed.z = -collision_dz * pushPower;
        }
    }
    // Dans le cas où les balles se trouvent au même endroit
    // On donne fait une petite répulsion
    else{
        spheres[i].position.x += 0.01f * (rand() % 100 - 50);
        spheres[i].position.z += 0.01f * (rand() % 100 - 50);
    }
    if (choix == 1){
        // Pour pas remplir le tableau d'espèces directement lors du chevauchement
        if ((currentTime - spheres[i].collisionTime > COLLISION_DELAY) &&
            (currentTime - spheres[j].collisionTime > COLLISION_DELAY) &&
            (spheres_counter < MAX_SPHERES)){
                t_color mix = combineColours(spheres[i].colour, spheres[j].colour);
                addSpecie(mix, 1);
                // Mise à jour du temps de la dernière collision
                spheres[i].collisionTime = currentTime;
                spheres[j].collisionTime = currentTime;
            }
    }
}

// Teste les collisions entre l'observateur et tous les êtres vivants
int check_observer_collision_beings(t_observer observer) {
    for (int i = 0; i < spheres_counter; i++) {
        if (is_observer_being_colliding(observer, spheres[i]))
            // Collision
            return 1;
    }

    return 0;
}