#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ipc.h>

#include "user.h"

void *createSHM() {
    return mmap(NULL, sizeof(Users), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

Users* getUsers() {
    static Users *users;

    if (users == NULL) {
        users = createUsers();
    }

    return users;
}

Users* createUsers() {
    Users   *users;

    users = (Users*) createSHM();
    if (users == MAP_FAILED) {
        perror("Can't create shared memory");
        exit(1);
    };

    users->size = 0;

    if (users == NULL) {
        puts("Error: malloc failed");
        exit(1);
    }

    users->users = malloc(sizeof(User) * 100); //TODO
    // users->users = malloc(sizeof(User) * users->size);
    if (users->users == NULL) {
        puts("Error: malloc failed");
        exit(1);
    }

    return users;
}


User* createUser(char* name, char token) {
    Users   *users;
    char    *newName;
    char tokenUser;
    static  color;



    users = getUsers();

    // users->users = realloc(users->users, sizeof(User) * (users->size + 1));
    // if (users->users == NULL) {
    //     puts("Error: malloc failed");
    //     exit(1);
    // }

    newName = malloc(sizeof(char) * (strlen(name) + 1));
    if (newName == NULL) {
        puts("Error: malloc failed");
        exit(1);
    }

    strcpy(newName, name);
    users->users[users->size].token = token;
    users->users[users->size].name = newName;
    users->users[users->size].token = token;
    return &users->users[users->size++];
};
