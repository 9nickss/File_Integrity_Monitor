/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** hash_file.c
*/

#include "../../include/fim.h"
#include <stdio.h>
#include <openssl/sha.h>

char *separate_name(const char *filename)
{
    char *str = strdup(filename);
    char *last_slash = strrchr(str, '/');

    if (last_slash != NULL)
        return strdup(last_slash + 1);
    return str;
}

char *hash_file_content(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    SHA256_CTX context;
    

    if (!file)
        return NULL;
    SHA256_Init(&context);
    return str;
}

void hash_filename(const char *filename)
{
    char *name = separate_name(filename);
    char *hash = hash_file_content(filename);

    if (hash) {
        printf("File: %s, Hash: %s\n", name, hash);
        free(hash);
    } else
        printf("Error hashing file %s\n", name);
    free(name);
}
