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
}
