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
#define PATRICK_SPHERE_COLOR { 1.0f, 0.7529f, 0.7961f }
#define SPONGEBOB_SPHERE_COLOR { 1.0f, 0.8196f, 0.0f }
#define SPPONGEPAT_SPHERE_COLOR { 1.0f, 0.7863f, 0.3981f }
#define DEFAULT_SPHERE_RADIUS 0.5

// Types

// // Sphere
typedef struct {
    t_point position;
    t_point speed;
    t_point previousSpeed;
    t_color colour;
    float radius;
} t_sphere;


// Prototypes des fonctions
// Fonction qui permet de détecter la collision entre deux sphères
int isSphereCollided(t_sphere s1, t_sphere s2);
// Fonction qui vérifie les collisions des sphères 2 à 2
void speciesCollisions();
// Rajoute une nouvelle espèce dans le monde
void addSpecie(t_color couleur);
// Avance l'espèce vers l'avant
void moveSpecie(t_sphere *s);
// Mets à jour la position de la sphere
void updateSpherePosition();
// Dessine les espèces
void drawSpecies();

#endif
