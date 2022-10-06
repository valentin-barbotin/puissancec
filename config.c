#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/dir.h>
#include <errno.h>

#include "user.h"
#include "utils.c"

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
bool setupGlobal(FILE* fd, char* data, struct globalConfig* globalConfig);
int readConfig();

gameConfig config;

#define CONFIG_GLOBAL config.globalConfig

/**
 * Parse global settings from file descriptor and update the globalConfig struct using pointers
 * @param {FILE*} File descriptor
 * @param {char*} char*data
 * @param {struct globalConfig*} video configuration of the game
 * @return bool true if success
 */
bool setupGlobal(FILE* fd, char* data, struct globalConfig* globalConfig) {
    char key[SIZE_DATA], value[SIZE_DATA];

    //check if key is blacklisted
    while (fgets(data, SIZE_DATA, fd), !feof(fd))
    {
        removeLineFeed(data);
        char firstChar = *data; // *data = data[0]
        if (firstChar == '[' || firstChar == '\0')
            break;
        // get key and value
        // read all until the first '='
        sscanf(data, "%[^=]=%s", key, value);

        switch (hash(key))
        {
            case c_lang:
                strcpy(globalConfig->lang, value);
                break;
            
            default:
                break;
        }
    }
    return true;
}


/**
 * Try to read game configuration file, then parse to parse it
 * @return {int} 0 on success, and 1 in case of failure
 */
int readConfig() {
    char* configFile = "../config.ini";
    FILE* fd = fopen(configFile, "r");
    if (fd == NULL) {
        return EXIT_FAILURE;
    }

    // to define
    char* data = calloc(SIZE_DATA, sizeof(char));
    if (data == NULL) {
        return EXIT_SUCCESS;
    }

    // const unsigned long ready = hash("ready");

    bool success = false;
    while (!feof(fd))
    {
        fgets(data, SIZE_DATA, fd);
        removeLineFeed(data);
        switch (hash(data))
        {
            case Global:
                puts("Setup global");
                success = setupGlobal(fd, data, &config.globalConfig);
                break;
            default:
                puts("DEFAULT");
                break;
        }
        if (!success) {
            return EXIT_FAILURE;
        }
    }

    // if !fd, then recreate config file
    // recreateConfig

    free(data);
    fclose(fd);
    return 0;
}