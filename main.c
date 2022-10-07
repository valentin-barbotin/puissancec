#include <stdlib.h>
#include <stdio.h>
#include "printGrille.h"

#include "utils.h"
#include "config.h"
#include "user.h"
#include "game.h"
#include "colors.h"

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
    // for (int i = BLACK; i < COLOR_COUNT; i++)
    // {
    //     printColoredChar(i, 'A' + i);
    // }

    Users *users = getUsers();

    char name[SIZE_DATA];
    char token[5];

    puts("Entrer le nom du joueur 1");
    fflush(stdin);
    fgets(name, SIZE_DATA, stdin);
    puts("\nEntrer le symbole du joueur 1");
    fflush(stdin);
    fgets(token, 2, stdin);
    removeLineFeed(name);

    //TODO check si username valide
    //TODO check si username deja pris
    createUser(name, *token);
    puts("\nEntrer le nom du joueur 2");
    fflush(stdin);
    fgets(name, SIZE_DATA, stdin);
    puts("\nEntrer le symbole du joueur 2");
    fflush(stdin);
    fgets(token, 2, stdin);

    removeLineFeed(name);

    createUser(name, *token);

    for (int i = 0; i < users->size; i++)
    {
        puts(users->users[i].name);
    }


    char ** grille = NULL;
    grille = init_grille(&config);
    //tmp

    startGame(users, &config, grille);
}
