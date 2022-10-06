#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

Users* getUsers() {
    static Users *users;

    if (users == NULL) {
        users = createUsers();
    }

    return users;
}

Users* createUsers() {
    Users   *users;

    users = malloc(sizeof(Users));
    users->size = 0;

    if (users == NULL) {
        puts("Error: malloc failed");
        exit(1);
    }

    users->users = malloc(sizeof(User) * users->size);
    if (users->users == NULL) {
        puts("Error: malloc failed");
        exit(1);
    }

    return users;
}


User* createUser(char* name) {
    Users   *users;
    char    *newName;

    users = getUsers();

    users->users = realloc(users->users, sizeof(User) * (users->size + 1));
    if (users->users == NULL) {
        puts("Error: malloc failed");
        exit(1);
    }

    newName = malloc(sizeof(char) * (strlen(name) + 1));
    if (newName == NULL) {
        puts("Error: malloc failed");
        exit(1);
    }

    strcpy(newName, name);

    users->users[users->size].name = newName;
    users->size++;
    return NULL;
};
