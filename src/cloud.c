/* 
* Module : cloud
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 25/05/2023
*/

#include "drawing.h"
#include "random.h"
#include "interaction.h"
#include "cloud.h"
  
// Variables globales
t_cloud clouds[MAX_CLOUDS];
int clouds_count = 0;
extern t_point platform_max_corner;


// Vérifie si la position du nuage est possible par rapport aux autres nuages
int check_cloud(t_cloud cloud) {
    // Par rapport aux autres arbres
    for (int i = 0; i < clouds_count; i++)
        // Intersection ?
        if (is_clouds_colliding(cloud, clouds[i]))
            return 0;

    return 1;
}

// Ajoute un nuage
int add_cloud(t_point position) {
    t_cloud cloud;

    // Nombre max de nuages
    if (clouds_count > MAX_CLOUDS) return 1;

    // Initialisation des champs du nuage
    cloud.position = position;
    cloud.gaz_balls_count = random_int(MIN_GAZ_BALLS, MAX_GAZ_BALLS);
    generate_gaz_balls(&cloud);

    // Vérification du nuage par rapport aux autres nuages
    if (!check_cloud(cloud)) return 0;

    // Ajout du nuage
    clouds[clouds_count++] = cloud;

    return 1;
}

// Génère les boules de gaz du nuage
void generate_gaz_balls(t_cloud *cloud) {
    // Couleurs
    t_color gaz_balls_colors[5] = {
        { 199 / 255.0f, 196 / 255.0f, 191 / 255.0f },
        { 199 / 255.0f, 190 / 255.0f, 191 / 255.0f },
        { 199 / 255.0f, 196 / 255.0f, 200 / 255.0f },
    };

    // Génération des boules de gaz
    for (int i = 0; i < cloud->gaz_balls_count; i++) {
        // Offsets aléatoires pour les boules de gaz
        float offsetX = random_float(-20, 20);
        float offsetY = random_float(-3, 3);
        float offsetZ = random_float(-20, 20);

        // Position de la boule de gaz par rapport à celle du nuage
        INIT_POINT(cloud->gaz_balls[i].position, offsetX, offsetY, offsetZ);

        // Taille aléatoire
        cloud->gaz_balls[i].radius = random_float(MIN_GAZ_BALL_RADIUS, MAX_GAZ_BALL_RADIUS);

        // Couleur du feuillage
        cloud->gaz_balls[i].color = gaz_balls_colors[random_int(0, 2)];
    }
}

// Dessine un nuage
void draw_cloud(t_cloud cloud) {
    // Boules de gaz
    for (int i = 0; i < cloud.gaz_balls_count; i++) {
        // Position exacte de la boule de gaz
        t_point exact_position = {
            cloud.position.x + cloud.gaz_balls[i].position.x,
            cloud.position.y + cloud.gaz_balls[i].position.y,
            cloud.position.z + cloud.gaz_balls[i].position.z,
        };

        // Dessin
        draw_sphere(exact_position, cloud.gaz_balls[i].radius, cloud.gaz_balls[i].color);
    }
}

// Dessine tous les nuages
void draw_clouds() {
    for (int i = 0; i < clouds_count; i++)
        draw_cloud(clouds[i]);
}

// Génère aléatoirement des nuages dans la zone située entre min et max
void generate_random_clouds(int count, t_point min, t_point max) {
    for (int i = 0; i < count && i < MAX_CLOUDS; i++) {
        int has_added = 0;
        
        while (!has_added) {
            t_point rand_point = random_point(min, max);
            rand_point.y = DEFAULT_CLOUD_Y;

            has_added = add_cloud(rand_point);
        }
    }
}

// Déplace le nuage
void move_cloud(t_cloud *cloud, t_vector vector) {

    // Nuage en dehors de la plateforme
    if (!is_cloud_inside(*cloud)) {
        static int first_print = 0;

        if (first_print == 0)
            PRINT_POINT(cloud->position);

        // On pose un écart de 5.0f pour que la réapparition du nuage se fasse plus élégamment
        INIT_POINT(cloud->position, platform_max_corner.x + 20.0f, cloud->position.y, cloud->position.z);

        if (first_print == 0) {
            PRINT_POINT(cloud->position);
            printf("\n");
            first_print = 1;
        }

        return;
    }

    // On déplace le nuage
    TRANSLATE_POINT(cloud->position, vector);
}

// Déplace tous les nuages par le vecteur
void move_clouds(t_vector vector) {
    for (int i = 0; i < clouds_count; i++)
        move_cloud(&clouds[i], vector);
}

// Déplace les nuages
void update_clouds_positions() {
    t_vector vector = {
        -0.025f, 0.0f, 0.0f
    };

    move_clouds(vector);
}