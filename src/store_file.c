/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** store_file.c
*/

#include "../include/fim.h"

char *get_absolute_path(const char *filename)
{
    char *absolute_path = malloc(PATH_MAX);

    if (!absolute_path)
        return NULL;
    if (realpath(filename, absolute_path) == NULL) {
        free(absolute_path);
        return NULL;
    } 
    return absolute_path;
}

int open_file(hashtable_t *hashtable, const char *filepath)
{
    FILE *file = fopen(filepath, "r");
    size_t len = 0;
    int read = 0;

    if (file == NULL) {
        perror("Error opening file");
        return 84;
    }
    if (hash_filename(&hashtable, filepath) == 84) {
        perror("Error hashing file");
        fclose(file);
        return 84;
    }
    fclose(file);
    return 0;
}

int store_file(hashtable_t *hashtable, char *filename)
{
    if (!filename) {
        fprintf(stderr, "Failed to store filepath");
        exit(84);
    }
    open_file(hashtable, filename);
    return 0;
}
