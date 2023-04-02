/* 
* Module : display
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 30/03/2023
*/

#include "GL/gl.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>
#include "display.h"

// Variables globales
void (*drawing_function)();
t_frustum frustum = DEFAULT_FRUSTUM;
t_point eye_position = DEFAULT_EYE_POSITION;
t_point target_position = DEFAULT_TARGET_POSITION;


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(frustum.left, frustum.right, frustum.bottom,
              frustum.top, frustum.near, frustum.far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye_position.x, eye_position.y, eye_position.z, 
        target_position.x, target_position.y, target_position.z, 
        0, frustum.top, 0);

    // Dessin
    (*drawing_function)();

    glutSwapBuffers();
}


