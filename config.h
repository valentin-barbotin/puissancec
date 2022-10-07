#if !defined(CONFIG_H)
#define CONFIG_H

    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>

    #define RANDOM_BOOL rand() % 2

    // n char + null-terminator
    #define SIZE_DATA 101
    // all with [] around

    //Global
    #define Global 7571859109182318
    #define c_lang 6385431463
    #define c_host 6385303139
    #define c_ip 5863486
    #define c_port 6385590602
    #define c_join 6385374677
    #define c_users 210730549111

    typedef struct globalConfig
    {
        char lang[255];
        unsigned short users;
        int host;
        int join;
        char ip[16];
        char port[6];
    } globalConfig;

    typedef struct gameConfig
    {
        struct globalConfig globalConfig;
    } gameConfig;

    //Prototypes
    int readConfig(gameConfig *config);

    bool setupGlobal(FILE* fd, char* data, struct globalConfig* globalConfig);
    void defaultConfig(gameConfig* config);
    int readConfig(gameConfig *config);

    #define CONFIG_GLOBAL config.globalConfig

#endif // MACRO


