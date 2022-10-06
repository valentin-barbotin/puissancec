#if !defined(CONFIG_H)
#define CONFIG_H

    #include <stdbool.h>
    #include <stdio.h>
    #define RANDOM_BOOL rand() % 2

    // n char + null-terminator
    #define SIZE_DATA 101
    // all with [] around

    //Global
    #define Global 7571859109182318
    #define c_lang 6385431463
    #define c_rows 6385662640
    #define c_columns 229462173423334

    typedef struct globalConfig
    {
        char lang[255];
        unsigned short rows;
        unsigned short columns;
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


