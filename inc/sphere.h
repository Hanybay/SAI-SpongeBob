/* 
* Module : Sphere
* Type : fichier en-tête
* Auteur : BAYAZID Hany
* Date de création : 21/05/2023
*/

#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "types.h"

// Constantes
#define MAX_SPHERES 100
#define MAX_SPHERE_STEPS 10
#define DEFAULT_SPHERE_COLOR { 1.0f, 0.0f, 0.0f }
#define DEFAULT_SPHERE_RADIUS 0.5

// Types

// // Sphere
typedef struct {
    t_point position;
    t_point speed;
    t_color colour;
    float radius;
} t_sphere;


// Prototypes des fonctions
// Fonction qui permet de détecter la collision entre deux sphères
int isSphereCollided(t_sphere s1, t_sphere s2);
// Rajoute une nouvelle espèce dans le monde
void addSpecie();
// Avance l'espèce vers l'avant
void moveSpecie(t_sphere s);
// Mets à jour la position de la sphere
void updateSpherePosition();
// Dessine les espèces
void drawSpecies();

#endif
