/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** store_file.c
*/

#include "../include/fim.h"

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

static char *get_file(int argc, char **argv)
{
    char *filepath = NULL;

    if (!argv[1]) {
        perror("Invalid argument");
        exit(84);
    }
    filepath = argv[1];
    return filepath;
}

int store_file(hashtable_t *hashtable, int argc, char **argv)
{
    char *filepath = NULL;

    filepath = get_file(argc, argv);
    if (!filepath) {
        fprintf(stderr, "Failed to store filepath");
        exit(84);
    }
    open_file(hashtable, filepath);
    return 0;
}
