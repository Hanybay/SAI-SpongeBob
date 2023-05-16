#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "transformations.h"

// Variables globales



// Fonction principale
int main(int argc, char const *argv[]) {
    t_matrix tm, mm, pm;
    t_point point;

    point.x = 0;
    point.y = 0;
    point.z = 0;

    pm = point_matrix(point);
    tm = translation_matrix(5, 5, 6);

    print_matrix(pm);
    printf("\n\n");
    print_matrix(tm);
    printf("\n\n");

    // am = sum_matrices(1, sm, tm);
    mm = product_matrices(1, tm, pm);
    print_matrix(mm);

    exit(EXIT_SUCCESS);
}
