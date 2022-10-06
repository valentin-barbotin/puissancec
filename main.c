#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int rows = 6;
    int columns = 7;

    char grille[rows][columns];

    for (int i = 0; i < rows ; ++i) {
        for (int j = 0; j < columns; ++j) {
            grille[i][j]='X';
        }
    }

    //affichage grille
    for (int i = 0; i < rows ; ++i) {
        for (int j = 0; j <  columns; ++j) {
            //printf("%c", grille[i][j]);
            if(j==columns-1){
                //printf("\n");
            }
        }
    }

    //affichage complet
    for (int i = 0; i < rows ; ++i) {
        printf("|");
        for (int j = 0; j <  columns; ++j) {
            printf("  %c  |",grille[i][j]);
            if(j==columns-1){
                printf("\n");
            }
        }
    }

    return 0;

}
