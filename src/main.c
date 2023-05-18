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

// Constantes
#define DEFAULT_FOV 45.0f
#define DEFAULT_CLIP_FRONT 0.1f
#define DEFAULT_CLIP_BACK 100.0f
#define DEFAULT_CAMERA_SPEED 3.0f

// Variables globales
float camera_horizontal_angle = 0.0f; // Angle horizontal de la caméra en degrés
float camera_vertical_angle = 0.0f;   // Angle vertical de la caméra en degrés
float camera_distance = 5.0f;         // Distance entre la caméra et sa cible
float camera_position_x = 1.0f,       // Coordonnée x de la position de la caméra
      camera_position_y = 1.0f,       // Coordonnée y de la position de la caméra
      camera_position_z = -3.0f;      // Coordonnée z de la position de la caméra
    


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
    float camera_target_x, camera_target_z, camera_target_y;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Caméra
    // // Calcul de la cible de la caméra
    camera_target_x = sin(camera_horizontal_angle * M_PI / 360.0f) * camera_distance + camera_position_x;
    camera_target_y = sin(camera_vertical_angle * M_PI / 180.0f) * camera_distance + camera_position_y;
    camera_target_z = cos(camera_horizontal_angle * M_PI / 360.0f) * camera_distance + camera_position_z;

    printf("-- x=%f y=%f z=%f\n", camera_target_x, camera_target_y, camera_target_z);

    gluLookAt(// Position de la caméra
              camera_position_x, camera_position_y, camera_position_z,
              // Point vers lequel la caméra regarde
              camera_target_x, camera_target_y, camera_target_z,
              // Direction "vers le haut" de la caméra
              0.0f, 1.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);  // Couleur de la plateforme
    glBegin(GL_QUADS);
        glVertex3f(-3.0f, 0.0f, -3.0f); // coin inférieur gauche
        glVertex3f( 3.0f, 0.0f, -3.0f); // coin inférieur droit
        glVertex3f( 3.0f, 0.0f,  3.0f); // coin supérieur droit
        glVertex3f(-3.0f, 0.0f,  3.0f); // coin supérieur gauche
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);  // Couleur des points
    glPointSize(3.0);            // Taille des points 
    glBegin(GL_POINTS);
        glVertex3f(0.0f, 0.0f, 0.0f); // Centre
    glEnd();

    glutSwapBuffers();
}

// Gère les événements de redimensionnement de la fenêtre
void reshape(int width, int height) {
    if(height == 0) height = 1; 
    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(DEFAULT_FOV, aspect, DEFAULT_CLIP_FRONT, DEFAULT_CLIP_BACK);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Gère les événements clavier
void keyboard(unsigned char key, int x, int y) {
    // Vitesse de rotation de la caméra en degrés par pression de touche
    const float camera_speed = DEFAULT_CAMERA_SPEED;

    switch (key) {
        case 'q': // Déplacement de la caméra vers la gauche
            camera_horizontal_angle += camera_speed;

            // Limiter l'angle pour éviter de regarder trop à gauche
            if (camera_horizontal_angle > 180.0f)
                camera_horizontal_angle = 180.0f;
            break;
        case 'd': // Déplacement de la caméra vers la droite
            camera_horizontal_angle -= camera_speed;

            // Limiter l'angle pour éviter de regarder trop à droite
            if (camera_horizontal_angle < -180.0f)
                camera_horizontal_angle = -180.0f;
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

// Fonction principale
int main(int argc, char **argv) {
    // Affichage de la notice d'utilisation
    help_notice();

    // Initialisation des paramètres OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("SpongeBob Universe");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    
    exit(EXIT_SUCCESS);
}

