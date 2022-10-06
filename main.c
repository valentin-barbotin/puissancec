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
   
    int multiGame = 0;
    int localGame = 0;
    int ipExiste = 0;
    int portExiste = 0;

    char *ip=calloc(16,sizeof(char));
    char *port= calloc(6,sizeof(char));

    //BOUCLE SUR LES PARAMETRES DES EXECUTABLES
    for(int i = 1; i < argc ; i++){
        if(strcmp(argv[i],"--help")==0 || strcmp(argv[i],"-?")==0){
            //affiche HELP
            puts("-h, --host              Start a game as host");
            puts("-i, --ip=127.0.0.1      IP to use");
            puts("-j, --join              Join a game");
            puts("-l, --local             Start a local game (default)");
            puts("-p, --port=3000         Port to use");
            puts("-?, --help              Give this help list");
            puts("  , --usage             Give a short usage message");
        }

        unsigned long long argSize = strlen(argv[i]);

        if(argSize>2){
            for(int j = 0;j<argSize;j++) {
                //TROUVER SI IL Y A IP
                if (argv[i][j] == 'i' && argv[i][j + 1] == 'p') {

                    puts("IP TROUVE");
                    if(ipExiste != 0){
                        puts("VOUS CONFIGUREZ DEJA L'IP");
                        exit;
                    }
                    ipExiste = 1;
                    int findEg = 0;

                    //CHERCHE LA VALEUR '=' ET LA POSITION
                    while (argv[i][findEg] != '=' && findEg < argSize) {
                        findEg++;
                    }

                    //REMPLIS LE TABLEAU IP
                    for (int k = findEg; k < argSize; k++) {
                        ip[k - findEg] = argv[i][k + 1];
                    }

                    puts(ip);
                }

                //TROUVER SI IL Y A PORT
                if (argv[i][j] == 'p' && argv[i][j + 1] == 'o') {

                    puts("PORT TROUVE");
                    if(portExiste != 0){
                        puts("VOUS CONFIGUREZ DEJA LE PORT");
                        exit;
                    }
                    portExiste = 1;
                    int findEg = 0;

                    //CHERCHE LA VALEUR '=' ET LA POSITION
                    while (argv[i][findEg] != '=' && findEg < argSize) {
                        findEg++;
                    }

                    //REMPLIS LE TABLEAU PORT
                    for (int k = findEg; k < argSize; k++) {
                        port[k - findEg] = argv[i][k + 1];
                    }

                    puts(port);
                }
            }
        }

        //VERIFIE SI ARGV EST I
        if(strcmp(argv[i],"-i")==0){
            //range dans ip l'adresse IP
            if(ipExiste != 0){
                puts("VOUS CONFIGUREZ DEJA L'IP");
                exit;
            }
            ipExiste = 1;
            i++;
            strcpy(ip,argv[i]);
            i++;
        }

        //VERIFIE SI ARGV EST join
        if(strcmp(argv[i],"-j")==0 || strcmp(argv[i],"--join")==0){
            //Rejoindre le jeu en multi
            multiGame = 1;
            printf("%d\n",multiGame);
        }

        //VERIFIE SI ARGV EST local
        if(strcmp(argv[i],"-l")==0 || strcmp(argv[i],"--local")==0){
            //Rejoindre le jeu en local
            localGame = 1;
            printf("%d\n",localGame);
        }

        //VERIFIE SI ARGV EST P
        if(strcmp(argv[i],"-p")==0){
            //range dans ip l'adresse IP
            if(portExiste != 0){
                puts("VOUS CONFIGUREZ DEJA LE PORT");
                exit;
            }
            portExiste = 1;
            i++;
            strcpy(port,argv[i]);
            i++;
        }

        //VERIFIE SI ARGV EST USAGE
        if(strcmp(argv[i],"--usage")==0){
            //Mettre une introduction pour l'usage de notre executable
            puts("Mettre une introduction pour l'usage de notre executable");
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
