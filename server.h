#if !defined(SERVER_H)
#define SERVER_H

#include "config.h"

void main_server(gameConfig *config, char **grid);
void handleClient(int clientSocket, int client, gameConfig *config, short *turn, char **grid);

#endif // MACRO
