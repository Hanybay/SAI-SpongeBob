#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/gl.h"
#include "transformations.h"

// Variables globales



// Fonction principale
int main(int argc, char const *argv[]) {
    GLfloat *tm = translation_matrix(5, 7, 8),
            *sm = scaling_matrix(1, 10, 3),
            *rxm = rotation_x_matrix(M_PI/4);
    print_matrix(tm, 16, 4);
    printf("\n\n");
    print_matrix(sm, 16, 4);
    printf("\n\n");
    print_matrix(rxm, 16, 4);
    exit(EXIT_SUCCESS);
}
