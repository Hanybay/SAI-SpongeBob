/* 
* Module : drawing
* Type : fichier en-tête
* Auteur : Mourtaza AKIL
* Date de création : 18/05/2023
*/

#ifndef _DRAWING_H_
#define _DRAWING_H_

#include "types.h"

// Constantes
#define DEFAULT_SPHERE_RESOLUTION 32
#define DEFAULT_SKYBOX_COLOR { 157 / 255.0f, 193 / 255.0f, 224 / 255.0f }


// Prototypes des fonctions
// Dessine un plus à la position donnée
void draw_plus(t_point position, float size, t_color color, float line_width);
// Dessine un plus en 2D à la position donnée (position.z inutile)
void draw_plus_2D(t_point position, float size, t_color color, float line_width);
// Dessine une ligne entre deux points
void draw_line(t_point corner1, t_point corner2, t_color color, float line_width);
// Dessine un cube
void draw_cube(t_point corner1, t_point corner2, t_color color);
// Dessine un cube avec des trous (corps d'une maison)
void draw_house_cube(t_point corner1, t_point corner2, t_color color, t_color door_color, t_color window_color);
// Dessine une sphère (ATTENTION ! Dessin à l'origine)
void draw_sphere(t_point position, float radius, t_color color);
// Dessine un cône tronqué
void draw_cone_truncated(t_point position, float bottom_base_radius, float top_base_radius, float height, int slices, int stacks, t_color color);
// Dessine un cylindre
void draw_cylinder(t_point position, float radius, float height, int slices, int stacks, t_color color);
// Dessine un ellipsoïde
void draw_ellipsoid(t_point position, float radius_x, float radius_y, float height, int slices, int stacks, t_color color);
// Dessine un prisme triangulaire
void draw_triangular_prism(t_point position, float base_width, float height, float depth, t_color color);
// Dessine une skybox
void draw_skybox(t_point position, float width);

#endif
