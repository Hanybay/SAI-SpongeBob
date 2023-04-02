#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "transformations.h"

// Variables globales



// Fonction principale
int main(int argc, char const *argv[]) {
    t_matrix sm, tm, am, test, mm;
    int dimensions[2] = { 4, 5 };


    sm = scaling_matrix(2, 3, 4);
    tm = translation_matrix(5, 5, 6);
    test = zero_matrix(dimensions);

    print_matrix(sm);
    printf("\n\n");
    print_matrix(tm);
    printf("\n\n");
    print_matrix(test);
    printf("\n\n");

    am = sum_matrices(1, sm, tm);
    mm = product_matrices(1, sm, tm);


    print_matrix(am);
    printf("\n\n");
    print_matrix(mm);

    exit(EXIT_SUCCESS);
}
