/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** check_file_hash.c
*/

#include "../../include/fim.h"

int check_changes(hashtable_t *hashtable)
{
    int changed = 0;
    hashtable_t *current = NULL;
    char *current_hash = NULL;

    if (!hashtable)
        return 84;
    current = hashtable;
    while (current) {
        current_hash = hash_file_content(current->filename);
        if (!current_hash) {
            printf("Warning: %s not accessible.\n", current->filename);
            changed = 1;
        }
        if (strcmp(current->hash, current_hash) != 0) {
            printf("Alert: File hash changed: %s\n", current->filename);
            changed = 1;
        }
        current = current->next;
    }
    return changed;
}
