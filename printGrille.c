//
// Created by fanny on 2022-10-06.
//
#include "printGrille.h"
#include <stdlib.h>
#include <stdio.h>

char ** init_grille(int rows, int columns){
    char ** grille = malloc( rows*sizeof(char*) );
    for (int i = 0; i < rows ; ++i) {
        grille[i] = malloc( columns*sizeof(char) );
        for (int j = 0; j < columns; ++j) {
            grille[i][j]='X';
        }
    }
    return grille;
}

void print_grille(char ** grille, int rows, int columns){
    //affichage grille
    for (int i = 0; i < rows ; ++i) {
        for (int j = 0; j <  columns; ++j) {
            printf("%c", grille[i][j]);
            if(j==columns-1){
                printf("\n");
            }
        }
    }
}

void print_all(char ** grille, int rows, int columns){
    //affichage complet
    for (int i = 0; i < rows ; ++i) {
        printf("|");
        for (int j = 0; j <  columns; ++j) {
            printf("   %c   |",grille[i][j]);
            if(j==columns-1){
                printf("\n");
            }
        }
    }
    char * numColumn[3];

    //affichage numeros colonne
    for (int j = 0; j <  columns; ++j) {
        sprintf(numColumn, "%d", j);
        printf("    %s   ",numColumn);
    }

}

