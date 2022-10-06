#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "config.h"
#include "user.h"
#include "game.h"

int main(int argc, char **argv) {

    // fill gameConfig using config file
    gameConfig config;
    defaultConfig(&config);
    if (readConfig(&config) == 1) {
        fprintf(stderr, "Erreur lors de la lecture du fichier de configuration");
        return EXIT_FAILURE;
    }

    //TODO: use cli arguments to override config file

    printf("Langue: %s\n", config.globalConfig.lang);

    puts("\033[1;31mHello World!\033[0m");

    Users *users = getUsers();

    createUser("valentin");
    createUser("fanny");
    createUser("kenny");

    for (int i = 0; i < users->size; i++)
    {
        puts(users->users[i].name);
    }
    int rows = 6;
    int columns = 7;

    char grille[rows][columns];

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


int main(int argc, char **argv) {
    int rows = 6;
    int columns = 7;

    char ** grille = NULL;

    grille = init_grille(rows, columns);
    print_all(grille, rows, columns);

    free(grille);

    return 0;

}
