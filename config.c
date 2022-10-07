#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include "user.h"
#include "utils.c"
#include "config.h"

/**
 * Parse global settings from file descriptor and update the globalConfig struct using pointers
 * @param {FILE*} File descriptor
 * @param {char*} char*datayo
 *
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
            case c_host:
                globalConfig->host = atoi(value);
                break;
            case c_ip:
                strcpy(globalConfig->ip, value);
                break;
            case c_port:
                strcpy(globalConfig->port, value);
                break;
            case c_join:
                globalConfig->join = atoi(value);
                break;
            default:
                break;
        }
    }
    return true;
}

/**
 * Fill the gameConfig struct with default values
 * @param {gameConfig*} game configuration of the game
 * @return void
 */
void defaultConfig(gameConfig* config) {
    strcpy(config->globalConfig.lang, "en");
}

/**
 * Try to read game configuration file, then parse to parse it
 * @param {gameConfig*} config struct
 * @return {int} 0 on success, and 1 in case of failure
 */
int readConfig(gameConfig *config) {
    char* configFile = "../config.ini";
    FILE* fd = fopen(configFile, "r");
    if (fd == NULL) {
        configFile = "./config.ini";
        fd = fopen(configFile, "r");
        if (fd == NULL) {
            return EXIT_FAILURE;
        }
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
                success = setupGlobal(fd, data, &config->globalConfig);
                break;
            default:
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