/* 
* Module : object
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 200/05/20023
*/

#include "drawing.h"
#include "object.h"


// Dessine le plan (axes x, y, z)
void draw_plane() {
    // Plan
    t_point origin, y_up, x_left, z_front;
    t_color y_axis_color, x_axis_color, z_axis_color;

    // // Origine
    INIT_POINT(origin, 0.0f, 0.0f, 0.0f);

    // // Axe des y
    INIT_POINT(y_up, 0.0f, 200.0f, 0.0f);
    INIT_COLOR(y_axis_color, 1.0f, 0.0f, 0.0f);
    draw_line(origin, y_up, y_axis_color, 3.0f);

    // // Axe des x
    INIT_POINT(x_left, 200.0f, 0.0f, 0.0f);
    INIT_COLOR(x_axis_color, 0.0f, 1.0f, 0.0f);
    draw_line(origin, x_left, x_axis_color, 3.0f);

    // // Axe des z
    INIT_POINT(z_front, 0.0f, 0.0f, 200.0f);
    INIT_COLOR(z_axis_color, 0.0f, 0.0f, 1.0f);
    draw_line(origin, z_front, z_axis_color, 3.0f);
}

// Dessine le viseur
void draw_view_finder(float window_width, float window_height) {
    t_point view_finder;
    t_color view_finder_color;

    INIT_POINT(view_finder, window_width / 2.0f, window_height / 2.0f, 0.0f);
    INIT_COLOR(view_finder_color, 0.0f, 1.0f, 0.0f);
    draw_plus_2D(view_finder, 20.0f, view_finder_color, 1.0f);
}