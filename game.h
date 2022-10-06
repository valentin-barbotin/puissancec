#if !defined(GAME_H)
#define GAME_H

#include "user.h"
#include "utils.h"

void            placeBlock(int row, int col);
User*           isBlock(int row, int col);

void            startGame(Users *users, gameConfig* config);

#endif // MACRO


