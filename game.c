#include <stdio.h>
#include <stdlib.h>

#include "user.h"
#include "config.h"
#include "printGrille.h"

void startGame(Users *users, gameConfig* config, char **grille) {
    // afficher grille
    int i;
    User *user;
    unsigned short colChoisie;
    short rows = config->globalConfig.rows;
    short columns = config->globalConfig.columns;
    print_all(grille, rows, columns);
    int indice=0;
    short myTurn=1;
    int remplies=0;

    user = NULL;
    do
    {
        for (i = 0; i < users->size; i++)
        {
            do
            {
                printf("Joueur %d: %s, Choisissez une colonne: \n", i + 1, users->users[i].name);
                scanf("%hu", &colChoisie);
                if(colChoisie < 1 || colChoisie > columns){
                    printf("Cette colonne n'existe pas !\n");
                }
            } while (colChoisie < 1 || colChoisie > columns);

            // si colonne pleine, redemander une colonne
            while (grille[0][colChoisie-1]!=' '){
                    printf("Cette colonne est pleine !\n");
                    printf("Joueur %d: %s, Choisissez une colonne: \n", i + 1, users->users[i].name);
                    scanf("%hu", &colChoisie);
            }

            printf("Vous avez choisi la colonne %hu\n", colChoisie);
            indice=rows-1;
            while(myTurn==1){
                if(grille[indice][colChoisie - 1]==' ') {
                    grille[indice][colChoisie - 1] = users->users[i].token;
                    remplies+=1;
                    myTurn=0;
                }
                --indice;
            }
            print_all(grille, rows, columns);


            //Vérification

            int count=0;

            //diagonales simples au milieu
            for (int k = 0; k < rows ; ++k) {
                if(grille[k][k] == users->users[i].token){
                    count++;
                }else{
                    count=0;
                }
                if(count==4){
                    printf("Joueur %d: %s, BRAVOOOOO !!! \n", i + 1, users->users[i].name);
                    return;
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
                    if(count==4){
                        printf("Joueur %d: %s, BRAVOOOOO !!! \n", i + 1, users->users[i].name);
                        return;
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
                    if(count==4){
                        printf("Joueur %d: %s, BRAVOOOOO !!! \n", i + 1, users->users[i].name);
                        return;
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

    } while (user == NULL);
    
}

#include "game.h"
