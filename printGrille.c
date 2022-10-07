//
// Created by fanny on 2022-10-06.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "printGrille.h"
#include "config.h"
#include "utils.h"

char **init_grille(gameConfig* config) {
    short rows = config->globalConfig.rows;
    short columns = config->globalConfig.columns;

    char **grille = createSHM(sizeof(char *) * rows);
    if (grille == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(1);
    }

    // char **grille = malloc( rows*sizeof(char*) );
    for (int i = 0; i < rows ; ++i) {
        // grille[i] = malloc( columns*sizeof(char) );
        grille[i] = createSHM(sizeof(char *) * rows);
        if (grille[i] == NULL) {
            perror("Erreur d'allocation de mémoire");
            exit(1);
        }
        for (int j = 0; j < columns; ++j) {
            grille[i][j]=' ';
        }
    }
    return grille;
}

void print_all(char ** grille, int rows, int columns) {
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

    //affichage numeros colonne
    for (int j = 1; j <= columns; ++j) {
        if(nombreChiffres(j) < 2){
            printf("   00%d  ", j);
        }else{
            printf("   0%d  ", j);
        }
    }
    printf("\n");
}


void print_all_multi(char ** grille, int rows, int columns, char *output) {
    //affichage complet
    char *tmp = malloc(sizeof(char) * 100);
    for (int i = 0; i < rows ; ++i) {
        sprintf(tmp, ("|"));
        strcat(output, tmp);
        for (int j = 0; j <  columns; ++j) {
            sprintf(tmp, "   %c   |",grille[i][j]);
            strcat(output, tmp);
            if(j==columns-1){
                sprintf(tmp, ("\n"));
                strcat(output, tmp);
            }
        }
    }

    //affichage numeros colonne
    for (int j = 1; j <= columns; ++j) {
        if(nombreChiffres(j) < 2){
            sprintf(tmp, "   00%d  ", j);
            strcat(output, tmp);
        }else{
            sprintf(tmp, "   0%d  ", j);
            strcat(output, tmp);
        }
    }
    sprintf(tmp, "\n");
    strcat(output, tmp);
}
