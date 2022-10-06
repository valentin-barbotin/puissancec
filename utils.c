#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Description
 * @todo handle differents breaklines
 * @param {char*} take a string and remove the break line
 * @return {void}
 */
void removeLineFeed(char* str) {
    str[strcspn(str, "\n")] = '\0';
}

// https://theartincode.stanis.me/008-djb2/
/**
 * Generate an "hash" of numbers from a string
 * Used to make switch case with string
 * @param {const char* str} the source string
 * @return {const unsigned long} the immutable generated hash
 */
const unsigned long hash(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
    
}
/**
 * Check if a string array contains a specific string
 * @param char** string array
 * @param char* the string to search
 * @param const int size of the array
 * @return {any}
 */
int doesInclude(char** array, const char* str, const int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(array[i], str) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Read an entire file, and store the content in the heap
 * @param src filePath
 * @return char* content location
 */
char* readFile(const char* src) {
    FILE* fd = fopen(src, "rb");
    if (fd == NULL) {
        return NULL;
    }

    fseek(fd, 0, SEEK_END);
    long size = ftell(fd);
    rewind(fd);
    char* data = malloc(size);
    if (data == NULL) {
        return NULL;
    }

    fread(data, sizeof(char), size, fd);
    data[size] = '\0';

    fclose(fd);
    return data;
}

/**
 * Remove suffix from a string
 * @param src char* src string
 * @param char* suffix to remove
 * @return char* suffix position in src
 */
char* removeSuffix(char* src, char* suffix) {
    char *pos = strstr(src, suffix);
    if (pos == NULL) {
        fprintf(stderr, "Can't find %s\n", suffix);
        exit(1);
    }
    *pos = '\0';
    return pos;
}


int nombreChiffres ( int nombre ){
    int i = 1;
    if (nombre < 0)
    {
        nombre = -nombre;
    }
    while (nombre >= 10)
    {
        nombre /= 10;
        i++;
    }
    return i;
}