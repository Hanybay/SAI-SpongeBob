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


// Affiche la notice d'utilisation
void help_notice() {
    fprintf(stdout, "\n/////////////////////////////NOM-PROJET//////////////////////////\n\n"
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Commencer à dessiner ici

    glutSwapBuffers();
}

// Gère les événement de redimensionnement de la fenêtre
void reshape(int width, int height) {
    if(height == 0) height = 1; 
    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Fonction principale
int main(int argc, char **argv) { 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("SpongeBob Universe");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    
    exit(EXIT_SUCCESS);
}

