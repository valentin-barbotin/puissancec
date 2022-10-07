#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "config.h"
#include "printGrille.h"
#include "game.h"

void winGame(Users *users, char **grille, gameConfig* config, char *output, int i) {
    if (output == NULL) {
        puts("");
        puts("");
        print_all(grille, config->globalConfig.rows, config->globalConfig.columns);
        printf("Joueur %d: %s, BRAVOOOOO !!! \n", i + 1, users->users[i].name);
    } else {
        char tmp[100];
        print_all_multi(grille, config->globalConfig.rows, config->globalConfig.columns, output);
        sprintf(tmp, "Joueur %d: %s, BRAVOOOOO !!! \n", i + 1, users->users[i].name);
        strcat(output, tmp);
    }
}

void game2(Users *users, gameConfig* config, char **grille, unsigned short colChoisie, int userIndex, User **user, char *output) {
    short rows = config->globalConfig.rows;
    short columns = config->globalConfig.columns;
    int indice=0;
    short myTurn=1;
    int remplies=0;
    int i = userIndex;

    indice=rows-1;
    while(myTurn==1) {
        if(grille[indice][colChoisie - 1]==' ') {
            grille[indice][colChoisie - 1] = users->users[i].token;
            remplies+=1;
            myTurn=0;
        }
        --indice;
    }
    if (output == NULL) {
        puts("");
        puts("");
        print_all(grille, rows, columns);
    } else {
        print_all_multi(grille, rows, columns, output);
    }

    //Vérification
    int count=0;

    //diagonales simples au milieu
    for (int k = 0; k < rows ; ++k) {
        if(grille[k][k] == users->users[i].token){
            count++;
        }else{
            count=0;
        }
        if(count==config->globalConfig.serie){
            winGame(users, grille, config, output, i);
            exit(0);
        }
    }
    count=0;

    //diagonales de gauche à droite
    for (int k = 0; k < columns-3 ; ++k) {
        for (int j = 0; j < rows-3; ++j) {
            if(grille[j][k] == users->users[i].token){
                count++;
                if(grille[j+1][k+1] == users->users[i].token){
                    count++;
                    if(grille[j+2][k+2] == users->users[i].token){
                        count++;
                        if(grille[j+3][k+3] == users->users[i].token){
                            count++;
                        }
                    }
                }
            }
            if(count==config->globalConfig.serie){
                winGame(users, grille, config, output, i);
                exit(0);
            }
        }
    }
    count=0;

    //diagonales de droite à gauche
    for (int k = columns-1; k > 3 ; --k) {
        for (int j = 0; j < rows -3 ; ++j) {
            if(grille[j][k] == users->users[i].token){
                count++;
                if(grille[j+1][k-1] == users->users[i].token){
                    count++;
                    if(grille[j+2][k-2] == users->users[i].token){
                        count++;
                        if(grille[j+3][k-3] == users->users[i].token){
                            count++;
                        }
                    }
                }
            }
            if(count==config->globalConfig.serie){
                winGame(users, grille, config, output, i);
                exit(0);
            }
        }
        count=0;
    }

    //Si tout est rempli
    if(remplies == rows * columns){
        printf("MATCH NUUUL !!! \n");
        return;
    }
    myTurn=1;
}

void startGame(Users *users, gameConfig* config, char **grille) {
    int i;
    User *user;
    unsigned short colChoisie;

    print_all(grille, config->globalConfig.rows, config->globalConfig.columns);

    do
    {
        for (i = 0; i < users->size; i++)
        {
            do
            {
                printf("Joueur %d: %s, Choisissez une colonne: \n", i + 1, users->users[i].name);
                scanf("%hu", &colChoisie);
                if (colChoisie < 1 || colChoisie > config->globalConfig.columns){
                    printf("Cette colonne n'existe pas !\n");
                }
            } while (colChoisie < 1 || colChoisie > config->globalConfig.columns);

            // si colonne pleine, redemander une colonne
            while (grille[0][colChoisie-1]!=' '){
                printf("Cette colonne est pleine !\n");
                printf("Joueur %d: %s, Choisissez une colonne: \n", i + 1, users->users[i].name);
                scanf("%hu", &colChoisie);
            }

            printf("Vous avez choisi la colonne %hu\n", colChoisie);
            game2(users, config, grille, colChoisie, i, &user, NULL);
        }
    } while (user == NULL);
}
