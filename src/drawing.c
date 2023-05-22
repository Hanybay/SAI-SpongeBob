/* 
* Module : drawing
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 18/05 / 2023
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "drawing.h"
#include "transformations.h"
  

// Dessine un plus à la position donnée
void draw_plus(t_point position, float size, t_color color, float line_width) {
    // Épaisseur des lignes
    glLineWidth(line_width);
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_LINES);
        // Ligne verticale
        glVertex3f(position.x, position.y - size / 2.0f, position.z);
        glVertex3f(position.x, position.y + size / 2.0f, position.z);

        // Ligne horizontale
        glVertex3f(position.x - size / 2.0f, position.y, position.z);
        glVertex3f(position.x + size / 2.0f, position.y, position.z);
    glEnd();
}

// Dessine un plus en 2D à la position donnée (position.z inutile)
void draw_plus_2D(t_point position, float size, t_color color, float line_width) {
    // Épaisseur des lignes
    glLineWidth(line_width);
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_LINES);
        // Ligne verticale
        glVertex2f(position.x, position.y - size / 2.0f);
        glVertex2f(position.x, position.y + size / 2.0f);

        // Ligne horizontale
        glVertex2f(position.x - size / 2.0f, position.y);
        glVertex2f(position.x + size / 2.0f, position.y);
    glEnd();
}

// Dessine une ligne entre deux points
void draw_line(t_point corner1, t_point corner2, t_color color, float line_width) {
    // Épaisseur des lignes
    glLineWidth(line_width);
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_LINES);
        glVertex3f(corner1.x, corner1.y, corner1.z);
        glVertex3f(corner2.x, corner2.y, corner2.z);
    glEnd();
}

// Dessine un cube
void draw_cube(t_point corner1, t_point corner2, t_color color) {
    // Faces du cube
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_QUADS);
        // Face avant
        glVertex3f(corner1.x, corner1.y, corner1.z);
        glVertex3f(corner2.x, corner1.y, corner1.z);
        glVertex3f(corner2.x, corner2.y, corner1.z);
        glVertex3f(corner1.x, corner2.y, corner1.z);

        // Face arrière
        glVertex3f(corner1.x, corner1.y, corner2.z);
        glVertex3f(corner2.x, corner1.y, corner2.z);
        glVertex3f(corner2.x, corner2.y, corner2.z);
        glVertex3f(corner1.x, corner2.y, corner2.z);

        // Face de droite
        glVertex3f(corner2.x, corner1.y, corner1.z);
        glVertex3f(corner2.x, corner1.y, corner2.z);
        glVertex3f(corner2.x, corner2.y, corner2.z);
        glVertex3f(corner2.x, corner2.y, corner1.z);

        // Face de gauche
        glVertex3f(corner1.x, corner1.y, corner1.z);
        glVertex3f(corner1.x, corner1.y, corner2.z);
        glVertex3f(corner1.x, corner2.y, corner2.z);
        glVertex3f(corner1.x, corner2.y, corner1.z);

        // Face supérieure
        glVertex3f(corner1.x, corner2.y, corner1.z);
        glVertex3f(corner2.x, corner2.y, corner1.z);
        glVertex3f(corner2.x, corner2.y, corner2.z);
        glVertex3f(corner1.x, corner2.y, corner2.z);

        // Face inférieure
        glVertex3f(corner1.x, corner1.y, corner1.z);
        glVertex3f(corner2.x, corner1.y, corner1.z);
        glVertex3f(corner2.x, corner1.y, corner2.z);
        glVertex3f(corner1.x, corner1.y, corner2.z);
    glEnd();
}

// Dessine une porte (fermée ou ouverte)
void draw_house_door(int is_open, t_point corner1, t_point corner2, t_color color) {

    // Porte ouverte ?
    if (is_open) {
        glPushMatrix();
        glTranslatef(corner1.x, corner1.y, corner1.z);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        glTranslatef(-corner1.x, -corner1.y, -corner1.z);
    }

    static int first_print = 1;
    if (first_print) {
        PRINT_POINT(corner1);
        PRINT_POINT(corner2);
        first_print = 0;
    }

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_QUADS);
        glVertex3f(corner1.x, corner1.y, corner1.z);
        glVertex3f(corner2.x, corner1.y, corner2.z);
        glVertex3f(corner2.x, corner2.y, corner2.z);
        glVertex3f(corner1.x, corner2.y, corner1.z);
    glEnd();

    if (is_open) {
        glPopMatrix();
    }
}

// Dessine la face avant d'une maison (porte + fenêtre)
void draw_house_front(t_point corner1, t_point corner2, 
    t_color wall_color, t_color door_color, t_color window_color) {
    float wall_width, wall_height, door_width, door_height, window_radius;
    t_point door_corner1, door_corner2, window_corner1, window_corner2;

    // Dimensions du mur
    wall_width = fabsf(corner2.x - corner1.x);
    wall_height = fabsf(corner2.y - corner1.y);

    // Porte
    // // Dimensions de la porte
    door_width = wall_width * 0.25f;
    door_height = wall_height * 0.8f;

    INIT_POINT(door_corner1, corner1.x + wall_width * 0.15, corner1.y, corner1.z);
    INIT_POINT(door_corner2, door_corner1.x + door_width, door_corner1.y + door_height, corner1.z);
    draw_house_door(1, door_corner1, door_corner2, door_color);

    // Fenêtre
    // // Dimensions de la fenêtre
    window_radius = wall_width * 0.3f;

    INIT_POINT(window_corner1, corner1.x + wall_width * 0.55, corner1.y + wall_height * 0.4, corner1.z);
    INIT_POINT(window_corner2, window_corner1.x + window_radius, window_corner1.y + window_radius, corner1.z);

    glColor4f(window_color.r, window_color.g, window_color.b, 0.5f);
    glBegin(GL_QUADS);
        glVertex3f(window_corner1.x, window_corner1.y, window_corner1.z);
        glVertex3f(window_corner2.x, window_corner1.y, window_corner2.z);
        glVertex3f(window_corner2.x, window_corner2.y, window_corner1.z);
        glVertex3f(window_corner1.x, window_corner2.y, window_corner1.z);
    glEnd();

    // Mur
    glColor3f(wall_color.r, wall_color.g, wall_color.b);
    glBegin(GL_QUADS);
        glVertex3f(corner1.x, corner1.y, corner1.z);
        glVertex3f(door_corner1.x, door_corner1.y, corner1.z);
        glVertex3f(door_corner1.x, corner2.y, corner1.z);
        glVertex3f(corner1.x, corner2.y, corner1.z);

        glVertex3f(door_corner1.x, door_corner2.y, corner1.z);
        glVertex3f(corner2.x, door_corner2.y, corner1.z);
        glVertex3f(corner2.x, corner2.y, corner1.z);
        glVertex3f(door_corner1.x, corner2.y, corner1.z);

        glVertex3f(door_corner2.x, corner1.y, corner1.z);
        glVertex3f(window_corner1.x, corner1.y, corner1.z);
        glVertex3f(window_corner1.x, window_corner2.y, corner1.z);
        glVertex3f(door_corner2.x, window_corner2.y, corner1.z);

        glVertex3f(window_corner2.x, corner1.y, corner1.z);
        glVertex3f(corner2.x, corner1.y, corner1.z);
        glVertex3f(corner2.x, window_corner2.y, corner1.z);
        glVertex3f(window_corner2.x, window_corner2.y, corner1.z);

        glVertex3f(window_corner1.x, corner1.y, corner1.z);
        glVertex3f(window_corner2.x, corner1.y, corner1.z);
        glVertex3f(window_corner2.x, window_corner1.y, corner1.z);
        glVertex3f(window_corner1.x, window_corner1.y, corner1.z);
    glEnd();
}

// Dessine un cube avec des trous (corps d'une maison)
void draw_house_cube(t_point corner1, t_point corner2, t_color color, t_color door_color, t_color window_color) {
    // Autres faces du cube
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_QUADS);
        // Face arrière
        glVertex3f(corner1.x, corner1.y, corner2.z);
        glVertex3f(corner2.x, corner1.y, corner2.z);
        glVertex3f(corner2.x, corner2.y, corner2.z);
        glVertex3f(corner1.x, corner2.y, corner2.z);

        // Face de droite
        glVertex3f(corner2.x, corner1.y, corner1.z);
        glVertex3f(corner2.x, corner1.y, corner2.z);
        glVertex3f(corner2.x, corner2.y, corner2.z);
        glVertex3f(corner2.x, corner2.y, corner1.z);

        // Face de gauche
        glVertex3f(corner1.x, corner1.y, corner1.z);
        glVertex3f(corner1.x, corner1.y, corner2.z);
        glVertex3f(corner1.x, corner2.y, corner2.z);
        glVertex3f(corner1.x, corner2.y, corner1.z);
    glEnd();

    // Face avant
    draw_house_front(corner1, corner2, color, door_color, window_color);
}

// Dessine une sphère
void draw_sphere(t_point position, float radius, t_color color) {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    glColor3f(color.r, color.g, color.b);
    glutSolidSphere(radius, DEFAULT_SPHERE_RESOLUTION, DEFAULT_SPHERE_RESOLUTION);

    glPopMatrix();
}

// Dessine un cône tronqué
void draw_cone_truncated(t_point position, float bottom_base_radius, float top_base_radius, float height, int slices, int stacks, t_color color) {
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(position.x, position.y, position.z);

    glColor3f(color.r, color.g, color.b);

    // Base inférieure
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.0f);  // Centre de la base
        for (int i = 0; i <= slices; ++i) {
            float theta = (float)i * 2.0f * M_PI / slices;
            float x = bottom_base_radius * cosf(theta);
            float y = bottom_base_radius * sinf(theta);
            glVertex3f(x, y, 0.0f);
        }
    glEnd();

    // Base supérieure
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, height);  // Centre du toit
        for (int i = 0; i <= slices; ++i) {
            float theta = (float)i * 2.0f * M_PI / slices;
            float x = top_base_radius * cosf(theta);
            float y = top_base_radius * sinf(theta);
            glVertex3f(x, y, height);
        }
    glEnd();

    // Paroi
    for (int i = 0; i < slices; i++) {
        float theta = (float)i * 2.0f * M_PI / slices;
        float next_theta = (float)(i + 1) * 2.0f * M_PI / slices;

        glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j <= stacks; j++) {
                float ratio = (float)j / stacks;
                float z = height * ratio;
                float radius = bottom_base_radius + (top_base_radius - bottom_base_radius) * ratio;

                float x = radius * cosf(theta);
                float y = radius * sinf(theta);
                glVertex3f(x, y, z);

                x = radius * cosf(next_theta);
                y = radius * sinf(next_theta);
                glVertex3f(x, y, z);
            }
        glEnd();
    }

    glPopMatrix();
}

// Dessine un cylindre
void draw_cylinder(t_point position, float radius, float height, int slices, int stacks, t_color color) {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    glColor3f(color.r, color.g, color.b);

    // Paroi
    for (int i = 0; i < slices; i++) {
        float theta = (float)i * 2.0f * M_PI / slices;
        float next_theta = (float)(i + 1) * 2.0f * M_PI / slices;

        glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j <= stacks; j++) {
                float z = height * (float)j / stacks;
                float x = radius * cosf(theta);
                float y = radius * sinf(theta);
                glVertex3f(x, y, z);

                x = radius * cosf(next_theta);
                y = radius * sinf(next_theta);
                glVertex3f(x, y, z);
            }
        glEnd();
    }

    // Base supérieure
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, height);  // Centre de la base
        for (int i = 0; i <= slices; ++i) {
            float theta = (float)i * 2.0f * M_PI / slices;
            float x = radius * cosf(theta);
            float y = radius * sinf(theta);
            glVertex3f(x, y, height);
        }
    glEnd();

    // Base inférieure
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.0f);  // Centre de la base
        for (int i = 0; i <= slices; ++i) {
            float theta = (float)i * 2.0f * M_PI / slices;
            float x = radius * cosf(theta);
            float y = radius * sinf(theta);
            glVertex3f(x, y, 0.0f);
        }
    glEnd();

    glPopMatrix();
}

// Dessine un ellipsoïde
void draw_ellipsoid(t_point position, float radius_x, float radius_y, float height, int slices, int stacks, t_color color) {
    glPushMatrix();
    glScalef(radius_x, radius_y, height);

    draw_cylinder(position, 1.0f, 1.0f, slices, stacks, color);

    glPopMatrix();
}

// Dessine un prisme triangulaire
void draw_triangular_prism(t_point position, float base_width, float height, float depth, t_color color) {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    glColor3f(color.r, color.g, color.b);

    glBegin(GL_TRIANGLES);
        // Base inférieure
        glVertex3f(-base_width / 2, -height / 2, -depth / 2);
        glVertex3f(base_width / 2, -height / 2, -depth / 2);
        glVertex3f(0.0f, height / 2, -depth / 2);

        // Base supérieure
        glVertex3f(-base_width / 2, -height / 2, depth / 2);
        glVertex3f(base_width / 2, -height / 2, depth / 2);
        glVertex3f(0.0f, height / 2, depth / 2);
    glEnd();

    glBegin(GL_QUADS);
        // Côté 1
        glVertex3f(-base_width / 2, -height / 2, -depth / 2);
        glVertex3f(base_width / 2, -height / 2, -depth / 2);
        glVertex3f(base_width / 2, -height / 2, depth / 2);
        glVertex3f(-base_width / 2, -height / 2, depth / 2);

        // Côté 2
        glVertex3f(base_width / 2, -height / 2, -depth / 2);
        glVertex3f(base_width / 2, -height / 2, depth / 2);
        glVertex3f(0.0f, height / 2, depth / 2);
        glVertex3f(0.0f, height / 2, -depth / 2);

        // Côté 3
        glVertex3f(-base_width / 2, -height / 2, -depth / 2);
        glVertex3f(-base_width / 2, -height / 2, depth / 2);
        glVertex3f(0.0f, height / 2, depth / 2);
        glVertex3f(0.0f, height / 2, -depth / 2);

    glEnd();

    glPopMatrix();
}
