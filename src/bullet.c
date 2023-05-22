/* 
* Module : bullet
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 20/05/2023
*/

#include <math.h>
#include "drawing.h"
#include "bullet.h"
  
// Variables globales
t_bullet bullets[MAX_BULLETS];
int bullets_count = 0;
extern float delta_time;


// Tire une balle (rajoute une balle dans le monde)
void shoot_bullet(t_point start, t_point end, float speed) {
    if (bullets_count >= MAX_BULLETS) return; // Max de balles atteint

    // Position de départ de la balle
    t_bullet *bullet = &bullets[bullets_count++];
    bullet->start = start;
    bullet->position = start;

    // Position d'arrivée de la balle
    bullet->end = end;

    // Vitesse de déplacement de la balle
    bullet->speed = speed;

    // Nombre de pas
    bullet->steps = 0;
}

// Fais avancer la balle
void move_forward_bullet(t_bullet *bullet) {
    // On avance d'un pas
    bullet->steps++;

    bullet->position.x = bullet->start.x + bullet->steps / 10. * (bullet->end.x - bullet->start.x);
    bullet->position.y = bullet->start.y + bullet->steps / 10. * (bullet->end.y - bullet->start.y);
    bullet->position.z = bullet->start.z + bullet->steps / 10. * (bullet->end.z - bullet->start.z);
}

// Met à jour les positions des balles
void update_bullets_positions() {
    int i = 0;

    while (i < bullets_count) {
        t_bullet *bullet = &bullets[i];

        // On fait avancer la balle d'un pas
        move_forward_bullet(bullet);

        PRINT_POINT(bullet->position);

        // Nombre de pas max
        if (bullet->steps > MAX_BULLET_STEPS) {
            bullets[i] = bullets[--bullets_count]; // Remplacement par la dernière balle active
            i--; // On retraite l'indice
        }

        i++; // Balle suivante
    }
}

// Dessine les balles
void draw_bullets() {
    const t_color bullet_color = DEFAULT_BULLET_COLOR;

    for (int i = 0; i < bullets_count; i++) {
        t_bullet *bullet = &bullets[i];
    
        draw_sphere(bullet->position, DEFAULT_BULLET_RADIUS, bullet_color);
    }
}