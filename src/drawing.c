/* 
* Module : drawing
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 18/05/2023
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "drawing.h"
  

// Dessine un plus à la position donnée
void drawPlus(t_point position, float size, t_color color, float line_width) {
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
void drawPlus2D(t_point position, float size, t_color color, float line_width) {
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
void drawLine(t_point corner1, t_point corner2, t_color color, float line_width) {
    // Épaisseur des lignes
    glLineWidth(line_width);
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_LINES);
        glVertex3f(corner1.x, corner1.y, corner1.z);
        glVertex3f(corner2.x, corner2.y, corner2.z);
    glEnd();
}

// Dessine un cube
void drawCube(t_point corner1, t_point corner2, t_color color) {
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

// Dessine une sphère
void drawSphere(t_point position, float radius, t_color color) {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    glColor3f(color.r, color.g, color.b);
    glutSolidSphere(radius, DEFAULT_SPHERE_RESOLUTION, DEFAULT_SPHERE_RESOLUTION);

    glPopMatrix(); 
}
