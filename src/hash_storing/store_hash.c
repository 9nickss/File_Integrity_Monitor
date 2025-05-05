/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** hash_to_storing.c
*/

#include "../../include/fim.h"

int load_from_file(hashtable_t **hashtable)
{
    FILE *hash_file = fopen("hashes.fim", "r");
    char filename_buffer[512] = {0};
    char hash_buffer[512] = {0};
    char line[1024];

    if (!hash_file)
        return 1;
    rewind(hash_file);
    while (fgets(line, sizeof(line), hash_file)) {
        if (sscanf(line, "%[^:]:%s", filename_buffer, hash_buffer) == 2) {
            add_to_hashtable(*hashtable, hash_buffer, filename_buffer);
        }
    }
    fclose(hash_file);
    return 0;
}

int check_if_in_file(FILE *hash_file, const char *hash, const char *filename)
{
    char line[1024];
    char temp_file[] = "temp_hashes.fim";
    FILE *temp = NULL;
    int found = 0;

    rewind(hash_file);
    while (fgets(line, sizeof(line), hash_file)) {
        char stored_filename[512] = {0};
        char stored_hash[512] = {0};
        
        if (sscanf(line, "%[^:]:%s", stored_filename, stored_hash) == 2) {
            if (strcmp(stored_filename, filename) == 0) {
                found = 1;
                if (strcmp(stored_hash, hash) == 0)
                    return 1;
                break;
            }
        }
    }
    return 0;
}

int add_to_file(hashtable_t *hashtable)
{
    hashtable_t *current = NULL;
    FILE *hash_file = fopen("hashes.fim", "a+");

    if (!hash_file)
        return 84;
    if (!hashtable) {
        fclose(hash_file);
        return 84;
    }
    current = hashtable;
    if (!current) {
        fclose(hash_file);
        return 84;
    }
    while (current) {
        if (current->hash && current->filename) {
            if (check_if_in_file(hash_file, current->hash, current->filename) == 0)
                fprintf(hash_file, "%s:%s\n", current->filename, current->hash);
        }
        current = current->next;
    }
    return 0;
}
