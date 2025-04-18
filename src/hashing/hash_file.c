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
    unsigned char buffer[4096];
    size_t bytes_read;

    if (!file)
        return NULL;
    SHA256_Init(&context);
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0)
        SHA256_Update(&context, buffer, bytes_read);
    fclose(file);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &context);
    char *hash_string = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (!hash_string)
        return NULL;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_string[i * 2], "%02x", hash[i]);
    }
    return hash_string;
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
