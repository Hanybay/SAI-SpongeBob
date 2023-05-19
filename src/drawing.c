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
void drawPlus(t_point position, float size, t_color color) {
    glBegin(GL_LINES);
        glColor3f(color.r, color.g, color.b);
        // Ligne verticale
        glVertex3f(position.x, position.y - size / 2.0f, position.z);
        glVertex3f(position.x, position.y + size / 2.0f, position.z);
        // Ligne horizontale
        glVertex3f(position.x - size / 2.0f, position.y, position.z);
        glVertex3f(position.x + size / 2.0f, position.y, position.z);
    glEnd();
}

// Dessine un plus en 2D à la position donnée (position.z inutile)
void drawPlus2D(t_point position, float size, t_color color) {
    glBegin(GL_LINES);
        glColor3f(color.r, color.g, color.b);
        // Ligne verticale
        glVertex2f(position.x, position.y - size / 2.0f);
        glVertex2f(position.x, position.y + size / 2.0f);
        // Ligne horizontale
        glVertex2f(position.x - size / 2.0f, position.y);
        glVertex2f(position.x + size / 2.0f, position.y);
    glEnd();
}

// Dessine une ligne entre deux points
void drawLine(t_point side1, t_point side2, t_color color) {
    glBegin(GL_LINES);
        glColor3f(color.r, color.g, color.b);
        glVertex3f(side1.x, side1.y, side1.z);
        glVertex3f(side2.x, side2.y, side2.z);
    glEnd();
}