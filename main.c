#include <stdlib.h>
#include <stdio.h>
#include "printGrille.h"

int main(int argc, char **argv) {
    int rows = 6;
    int columns = 7;

    char ** grille = NULL;

    grille = init_grille(rows, columns);
    print_all(grille, rows, columns);

    free(grille);

    return 0;

}
