#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "types.h"
#include "display.h"


// Variables globales
extern t_point eye_position, target_position;
int angle = DEFAULT_ANGLE, step = DEFAULT_ANGLE_STEP;
float distance = DEFAULT_DISTANCE;


// Affiche la notice d'utilisation
void help_notice() {
    fprintf(stdout, "\n///////////////////////SPONGE-BOB-UNIVERSE///////////////////////\n\n"
                    "\n- Les 5 touches suivantes sont interactives :\n"
                    "\n-----------------------------------------------------------------\n\n"
                    "    'a'            :    change le sens de rotation.\n"
                    "    '+'            :    augmente le zoom (rapproche l'observateur).\n"
                    "    '-'            :    réduit le zoom (éloigne l'observateur).\n"
                    "    '[ESPACE]'     :    stoppe la rotation.\n"
                    "    '[GAUCHE]'     :    déplace l'observateur vers la gauche.\n"
                    "    '[DROITE]'     :    déplace l'observateur vers la droite.\n"
                    "    '[AVANT]'      :    avance l'observateur.\n"
                    "    '[ARRIERE]'    :    recule l'observateur.\n"
                    "\n-----------------------------------------------------------------\n\n");
}


// Fonction qui fera les dessins lors de l'affichage
void drawing() {
    glBegin(GL_QUADS);

    glVertex3f(DEFAULT_DISTANCE, 0, -DEFAULT_DISTANCE);
    glVertex3f(-DEFAULT_DISTANCE, 0, -DEFAULT_DISTANCE);
    glVertex3f(-DEFAULT_DISTANCE, 0, DEFAULT_DISTANCE);
    glVertex3f(DEFAULT_DISTANCE, 0, DEFAULT_DISTANCE);

    glEnd();
}


// Réalise les calculs
void update() {
    float angle_rad;

    // Rotation
    angle += step;

    // Conversion en radians
    angle_rad = (angle % 360) * M_PI / 180;

    // Calcule des coordonnées de la position de l'oeil
    eye_position.x = distance * sin(angle_rad);
    // eye_position.y = distance * cos(angle_rad);
    // eye_position.z = z_direction * eye_position.y;
    eye_position.z = distance * cos(angle_rad);

    glutPostRedisplay();
}


// Réalise les calculs lors de la détection d'une touche
void keyboard(unsigned char key, int x, int y) {

    switch (key) {
    case 'a':
        step = -step;
        glutPostRedisplay();
        break;
    case '-':
        if (distance <= DEFAULT_DISTANCE * 1.5) {
            distance += DEFAULT_DISTANCE * 0.05;
            glutPostRedisplay();
        }
        break;
    case '+':
        if (distance >= DEFAULT_DISTANCE * 0.5) {
            distance += -DEFAULT_DISTANCE * 0.05;
            glutPostRedisplay();
        }
        break;
    case ' ':
        static int space_pressed = 0;
        if (!space_pressed) {
            glutIdleFunc(NULL);
            space_pressed = 1;
        } else {
            glutIdleFunc(update);
            space_pressed = 0;
        }
    }
}


void special_keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            target_position.z -= DEFAULT_MOVE_STEP;
            eye_position.z -= DEFAULT_MOVE_STEP;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            target_position.z += DEFAULT_MOVE_STEP;
            eye_position.z += DEFAULT_MOVE_STEP;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            target_position.x -= DEFAULT_MOVE_STEP;
            eye_position.x -= DEFAULT_MOVE_STEP;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            target_position.x += DEFAULT_MOVE_STEP;
            eye_position.x += DEFAULT_MOVE_STEP;
            glutPostRedisplay();
    }
}


int main(int argc, char *argv[]) {
    extern void (*drawing_function)();

    // Intialisations
    drawing_function = drawing;
    // t = intersection_ktree(t1, t2);

    // Notice
    help_notice();

    // Initialisation de la fenêtre
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 500) / 2.5,
                           (glutGet(GLUT_SCREEN_HEIGHT) - 500) / 2);
    glutCreateWindow("SpongeBob Universe");
    glEnable(GL_DEPTH_TEST);

    // Fonctions appelées
    glutDisplayFunc(display);
    // glutIdleFunc(update);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);

    glutMainLoop();
    // glutExit();

    exit(EXIT_SUCCESS);
}