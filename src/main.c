#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "types.h"
#include "display.h"
#include "view.h"


// Affiche la notice d'utilisation
void help_notice() {
    fprintf(stdout, "\n///////////////////////SPONGE-BOB-UNIVERSE///////////////////////\n\n"
                    "\n- Les touches suivantes sont interactives :\n"
                    "\n-----------------------------------------------------------------\n\n"
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

// Réalise les calculs lors de la détection d'une touche
void keyboard(unsigned char key, int x, int y) {
}

void special_keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            move_front();
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            move_back();
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            move_left();
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            move_right();
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
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2);
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