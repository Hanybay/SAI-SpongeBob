/* 
* Module : principal
* Type : fichier source
* Auteur : Mourtaza AKIL
* Date de création : 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "types.h"
#include "view.h"
#include "drawing.h"

// Variables globales
float camera_horizontal_angle = 0.0f;        // Angle horizontal de la caméra en degrés
float camera_vertical_angle = 0.0f;          // Angle vertical de la caméra en degrés
t_point camera_position = {                  // Position de la caméra
    1.0f, 1.0f, -3.0f
};
float camera_distance = 5.0f;                // Distance entre la caméra et sa cible
float window_width = DEFAULT_WINDOW_WIDTH,   // Largeur de la fenêtre
      window_height = DEFAULT_WINDOW_HEIGHT; // Hauteur de la fenêtre
float aspect;


// Affiche la notice d'utilisation
void help_notice() {
    fprintf(stdout, "\n////////////////////////SPONGEBOB UNIVERSE///////////////////////\n\n"
                    "\n\n"
                    "\n-----------------------------------------------------------------\n\n"
                    "\n\n"
                    "\n-----------------------------------------------------------------\n\n");
}


// Affiche la notice d'utilisation du programme
void usage(char * programme, char * message, ...) {
    va_list arg;
    va_start(arg, message);
    if (strlen(message) != 0) {
        fprintf(stderr, "- Message -> ");
        vfprintf(stderr, message, arg);
        if (message[strlen(message) - 2] != '\n')
            fprintf(stderr, "\n");
        fprintf(stderr, "\n");
    }
    va_end(arg);
    fprintf(stderr, "- Usage : %s \n",
            programme);
    exit(EXIT_FAILURE);
}

// Réalise l'affichage
void display() {
    // Caméra
    t_point camera_target;
    // Viseur
    t_point view_finder;
    t_color view_finder_color;
    // Plan
    t_point origin, y_up, x_left, z_front;
    t_color y_axis_color, x_axis_color, z_axis_color;
    // Cube
    t_point corner1, corner2;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Projection perspective pour le rendu 3D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(DEFAULT_FOV, aspect, DEFAULT_CLIP_FRONT, DEFAULT_CLIP_BACK);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Caméra
    // // Calcul de la cible de la caméra
    camera_target.x = sin(camera_horizontal_angle * M_PI / 360.0f) * camera_distance + camera_position.x;
    camera_target.y = sin(camera_vertical_angle * M_PI / 180.0f) * camera_distance + camera_position.y;
    camera_target.z = cos(camera_horizontal_angle * M_PI / 360.0f) * camera_distance + camera_position.z;

    gluLookAt(// Position de la caméra
              camera_position.x, camera_position.y, camera_position.z,
              // Point vers lequel la caméra regarde
              camera_target.x, camera_target.y, camera_target.z,
              // Direction "vers le haut" de la caméra
              0.0f, 1.0f, 0.0f);

    // Plateforme
    glColor3f(1.0f, 1.0f, 1.0f);  // Couleur de la plateforme
    glBegin(GL_QUADS);
        glVertex3f(-3.0f, 0.0f, -3.0f); // Coin inférieur gauche
        glVertex3f( 3.0f, 0.0f, -3.0f); // Coin inférieur droit
        glVertex3f( 3.0f, 0.0f,  3.0f); // Coin supérieur droit
        glVertex3f(-3.0f, 0.0f,  3.0f); // Coin supérieur gauche
    glEnd();

    // Plan
    // // Origine
    INIT_POINT(origin, 0.0f, 0.0f, 0.0f);

    // // Axe des y
    INIT_POINT(y_up, 0.0f, 10.0f, 0.0f);
    INIT_COLOR(y_axis_color, 1.0f, 0.0f, 0.0f);
    drawLine(origin, y_up, y_axis_color, 3.0f);

    // // Axe des x
    INIT_POINT(x_left, 10.0f, 0.0f, 0.0f);
    INIT_COLOR(x_axis_color, 0.0f, 1.0f, 0.0f);
    drawLine(origin, x_left, x_axis_color, 3.0f);

    // // Axe des z
    INIT_POINT(z_front, 0.0f, 0.0f, 10.0f);
    INIT_COLOR(z_axis_color, 0.0f, 0.0f, 1.0f);
    drawLine(origin, z_front, z_axis_color, 3.0f);

    // Dessin d'un cube
    INIT_POINT(corner2, 1.0f, 1.0f, 1.0f);
    drawCube(origin, corner2, y_axis_color);

    // Projection orthogonale pour le rendu 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, window_width, window_height, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    INIT_POINT(view_finder, window_width / 2.0f, window_height / 2.0f, 0.0f);
    INIT_COLOR(view_finder_color, 0.0f, 1.0f, 0.0f);
    drawPlus2D(view_finder, 20.0f, view_finder_color, 1.0f);

    glutSwapBuffers();
}

// Gère les événements de redimensionnement de la fenêtre
void reshape(int width, int height) {
    if(height == 0) height = 1; 
    aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(DEFAULT_FOV, aspect, DEFAULT_CLIP_FRONT, DEFAULT_CLIP_BACK);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Récupèration des nouvelles dimensions
    window_height = height;
    window_width = width;
}

// Gère les événements clavier
void keyboard(unsigned char key, int x, int y) {
    // Vitesse de rotation de la caméra en degrés par pression de touche
    const float camera_speed = DEFAULT_CAMERA_SPEED;

    switch (key) {
        case 'q': // Déplacement de la caméra vers la gauche
            camera_horizontal_angle += camera_speed;

            // Limiter l'angle pour éviter de regarder trop à gauche
            if (camera_horizontal_angle > 179.0f)
                camera_horizontal_angle = 179.0f;

            // Mise à jour des vecteurs de déplacement
            rotate_movement_vectors(camera_vertical_angle, camera_horizontal_angle);
            break;
        case 'd': // Déplacement de la caméra vers la droite
            camera_horizontal_angle -= camera_speed;

            // Limiter l'angle pour éviter de regarder trop à droite
            if (camera_horizontal_angle < -179.0f)
                camera_horizontal_angle = -179.0f;

            // Mise à jour des vecteurs de déplacement
            rotate_movement_vectors(camera_vertical_angle, camera_horizontal_angle);  
            break;
        case 's': // Déplacement de la caméra vers le bas
            camera_vertical_angle -= camera_speed;

            // Limiter l'angle pour éviter de regarder trop bas
            if (camera_vertical_angle < -45.0f)
                camera_vertical_angle = -45.0f;
            break;
        case 'z': // Déplacement de la caméra vers le haut
            camera_vertical_angle += camera_speed;
            
            // Limiter l'angle pour éviter de regarder trop haut
            if (camera_vertical_angle > 45.0f)
                camera_vertical_angle = 45.0f;
            break;
    }

    glutPostRedisplay();
}

// Gère les événements clavier spécial
void special_keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            move_forward();
            break;
        case GLUT_KEY_DOWN:
            move_back();
            break;
        case GLUT_KEY_LEFT:
            move_left();
            break;
        case GLUT_KEY_RIGHT:
            move_right();
    }

    glutPostRedisplay();
}

// Fonction principale
int main(int argc, char **argv) {
    // Affichage de la notice d'utilisation
    help_notice();

    // Initialisation des paramètres OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("SpongeBob Universe");

    // Fonctions gérant la fenêtre et ces événements
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    
    exit(EXIT_SUCCESS);
}

