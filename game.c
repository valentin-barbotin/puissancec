#include <stdio.h>
#include <stdlib.h>

#include "user.h"
#include "config.h"
#include "printGrille.h"

void startGame(Users *users, gameConfig* config, char **grille) {
    // afficher grille
    int     i;
    User    *user;
    unsigned short   col;
    print_all(grille, config->globalConfig.rows, config->globalConfig.columns);

    // tant que pas fini
        // afficher joueur courant
        // demander coordonnees
        // placer pion
        // verifier si gagne
        // changer joueur courant

    user = NULL;
    do
    {
        for (i = 0; i < users->size; i++)
        {
            printf("Joueur %d: %s, Choisissez une colonne: \n", i + 1, users->users[i].name);

            do
            {
                scanf("%hu", &col);
            } while (col < 1 || col > 10);
            // } while (col < 1 || col > config->gameConfig.columns);

            // si colonne pleine, redemander une colonne
            
            // placeBlock(i, col);
            printf("Vous avez choisi la colonne %hu\n", col);

            // prendre le bas de la colonne
            // si case vide
                // placer pion
                // verifier si gagne
                // changer joueur courant
            // sinon
                // si colonne pleine
                    // redemander une colonne
                // regarder case du dessus
                // si case vide
                    // placer pion
                    // verifier si gagne
                    // changer joueur courant
                // sinon
                    //etc
        }
    } while (user == NULL);
    
}

#include "game.h"
