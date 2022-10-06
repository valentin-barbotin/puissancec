#if !defined(CONFIG_H)
#define CONFIG_H

    #define RANDOM_BOOL rand() % 2

    // n char + null-terminator
    #define SIZE_DATA 101
    // all with [] around

    //Global
    #define Global 7571859109182318
    #define c_lang 6385431463

    typedef struct globalConfig
    {
        char lang[255];
    } globalConfig;

    typedef struct gameConfig
    {
        struct globalConfig globalConfig;
    } gameConfig;

    //Prototypes
    int readConfig();

    bool setupGlobal(FILE* fd, char* data, struct globalConfig* globalConfig);
    void defaultConfig(gameConfig* config);
    int readConfig(gameConfig *config);

    #define CONFIG_GLOBAL config.globalConfig

#endif // MACRO


