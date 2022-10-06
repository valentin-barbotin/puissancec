#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "user.h"
#include "game.h"

int main(int argc, char **argv) {

    puts("\033[1;31mHello World!\033[0m");

    Users *users = getUsers();

    createUser("valentin");
    createUser("fanny");
    createUser("kenny");

    for (int i = 0; i < users->size; i++)
    {
        puts(users->users[i].name);
    }
}
