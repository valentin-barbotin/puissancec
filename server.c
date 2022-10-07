#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "config.h"
#include "server.h"
#include "user.h"

void sendPromptToClient(int clientSocket, char *message) {
    uint32_t dataLen = strlen(message);
    uint32_t hostToNetInt = htonl(dataLen);
    send(clientSocket, &hostToNetInt, sizeof(hostToNetInt), 0);
    if (dataLen > 0) {
        send(clientSocket, message, dataLen, 0);
    }
}

int isMyTurn(User *user) {
    Users *users = getUsers();
    return 1;
}

int enoughPlayers(gameConfig *config) {
    return (getUsers()->size == config->globalConfig.users) ? 1 : 0;
}

void main_server(gameConfig *config) {
    struct sockaddr_in srv, client;
    int sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    srv.sin_port = htons(atoi(config->globalConfig.port));
    srv.sin_addr.s_addr = inet_addr("0.0.0.0");
    srv.sin_family = AF_INET;

    if (bind(sd, (struct sockaddr *)&srv, sizeof(struct sockaddr_in)) < 0) {
        perror("Can't bind");
        exit(1);
    }

    listen(sd, 10);

    int clientId = 1;
    short *turn = (short*) createSHM();
    *turn = 0;

    do
    {
        int sz = sizeof(struct sockaddr_in);
        int clientSocket = accept(sd, (struct sockaddr *) &client, (socklen_t*) &sz);
        if (clientSocket == -1) {
            perror("rip le socket");
            exit(1);
        }
        clientId++;

        int forked = fork();
        if (forked == 0) { //handle single client
            printf("[Child] New client with id %d\n", clientId);
            handleClient(clientSocket, clientId, config, turn);
            return;
        }
        printf("[Main] New client with id %d\n", clientId);
    } while (1);
}

void handleClient(int clientSocket, int client, gameConfig *config, short *turn) {
    char data[500] = {0};
    char promptClient[1000];
    int  valid = 0;
    User    *currentUser;
    int    currentUserOrder;

    unsigned int length = 0;
    ssize_t resSize = 0;
    char *welcomeMsg = "Welcome to the game";

    uint32_t dataLen = strlen(welcomeMsg);
    uint32_t hostToNetInt = htonl(dataLen);
    send(clientSocket, &hostToNetInt, sizeof(hostToNetInt), 0);
    send(clientSocket, welcomeMsg, dataLen, 0);

    do
    {
        strcpy(promptClient, welcomeMsg);
        if (!valid) {
            strcpy(promptClient, welcomeMsg);
        }
        if (enoughPlayers(config)) {
            if (isMyTurn(currentUser)) {
                strcpy(promptClient, "Choisir une colonne: ");
            } else {
                strcpy(promptClient, "TODO: wait for opponent");
            }
        } else {
            strcpy(promptClient, "En attente d'autres joueurs...");
        }
            // strcpy(promptClient, "welcomeMsg");
        // demander au client
        // puts("send prompt to client");
        sendPromptToClient(clientSocket, promptClient);
        puts("send prompt to client OK");
        memset(data, 0, 500);

        //recevoir reponse
        if (resSize = recv(clientSocket, data, 500, 0), resSize == -1) {
            perror("bye");
            exit(1);
        };

        if ((enoughPlayers(config)) && (isMyTurn(currentUser))) {
            // placer jeton

            *turn += 1;
        }

        if (!valid) {
            currentUser = createUser(data, 'X');
            currentUserOrder = currentUser - getUsers()->users;
            char rrrrr[100];
            sprintf(rrrrr, "touch /tmp/puissancec_%d", currentUserOrder);
            system(rrrrr);
            valid = 1;
        } else {
            // game
            // TODO
            // if (isMyTurn()) { // c'est son tour
            
            // } else {

            // }
        }

        hostToNetInt = htonl(0);
        send(clientSocket, &hostToNetInt, sizeof(hostToNetInt), 0);
    } while (1);
}