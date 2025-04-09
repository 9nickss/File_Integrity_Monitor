/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** store_file.c
*/

#include "../include/fim.h"

int read_file(const char *filepath)
{
    FILE *file = fopen(filepath, "r");
    char *buffer = NULL;
    size_t len = 0;
    int read = 0;

    if (file == NULL) {
        perror("Error opening file");
        exit(84);
    }
    hash_filename(filepath);
    while ((read = getline(&buffer, &len, file) != -1)) {
        hash_buffer(buffer);
    }
    if (ferror(file)) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        exit(84);
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

int store_file(int argc, char **argv)
{
    char *filepath = NULL;

    filepath = get_file(argc, argv);
    if (!filepath) {
        fprintf(stderr, "Failed to store filepath");
        exit(84);
    }
    read_file(filepath);
    return 0;
}
