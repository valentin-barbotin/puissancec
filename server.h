#if !defined(SERVER_H)
#define SERVER_H

#include "config.h"

void main_server(gameConfig *config);
void handleClient(int clientSocket, int client, gameConfig *config, short *turn);

#endif // MACRO
