/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** hash_to_storing.c
*/

#include "../../include/fim.h"

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
        if (current->hash && current->filename)
            fprintf(hash_file, "%s:%s\n", current->filename, current->hash);
        current = current->next;
    }
    return 0;
}
