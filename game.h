#if !defined(GAME_H)
#define GAME_H

#include "user.h"
#include "utils.h"

void            placeBlock(int row, int col);
User*           isBlock(int row, int col);

void            startGame(Users *users, gameConfig* config, char **grille);
void            game2(Users *users, gameConfig* config, char **grille, unsigned short colChoisie, int userIndex, User **user, char *output);


#endif // MACRO
