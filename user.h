#if !defined(USER_H)
#define USER_H

typedef struct User {
    char token;
    char *name;
    char *placedToken;
} User;

typedef struct Users
{
    User            *users;
    unsigned int    size;
} Users;

User*           createUser(char* name, char token);
Users*          createUsers();
Users*          getUsers();

#endif // MACRO


