#include <stdlib.h>
#include <stdio.h>
#include "printGrille.h"
#include <string.h>

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

   
    for(int i = 1; i < argc ; i++){
        if(strcmp(argv[i],"--help")==0 || strcmp(argv[i],"-?")==0){
            puts("-h, --host              Start a game as host");
            puts("-i, --ip=127.0.0.1      IP to use");
            puts("-j, --join              Join a game");
            puts("-l, --local             Start a local game (default)");
            puts("-p, --port=3000         Port to use");
            puts("-?, --help              Give this help list");
            puts("  , --usage             Give a short usage message");
        }
    }

    printf("Langue: %s\n", config.globalConfig.lang);

    puts("\033[1;31mHello World!\033[0m");
    // for (int i = BLACK; i < COLOR_COUNT; i++)
    // {
    //     printColoredChar(i, 'A' + i);
    // }

    Users *users = getUsers();

    char name[SIZE_DATA];

    puts("Entrer le nom du joueur 1");
    fgets(name, SIZE_DATA, stdin);
    removeLineFeed(name);

    //TODO check si username valide
    //TODO check si username deja pris
    createUser(name);

    puts("Entrer le nom du joueur 2");
    fgets(name, SIZE_DATA, stdin);
    removeLineFeed(name);

    createUser(name);

    for (int i = 0; i < users->size; i++)
    {
        puts(users->users[i].name);
    }


    int rows = 6;
    int columns = 7;

    char ** grille = NULL;

    grille = init_grille(rows, columns);
    print_all(grille, rows, columns);


    //tmp
    startGame(users, &config);
}
