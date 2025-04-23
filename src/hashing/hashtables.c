/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** hashtables.c
*/

#include "../../include/fim.h"

hashtable_t *add_to_hashtable(hashtable_t *hashtable, char *hash, char *filename)
{
    hashtable_t *current = NULL;
    hashtable_t *prev = NULL;
    hashtable_t *new_node = NULL;

    if (!hashtable || !hash || !filename)
        return NULL;
    current = hashtable;
    if (current) {
        if (hashtable->filename == NULL && hashtable->hash == NULL) {
            hashtable->filename = strdup(filename);
            if (!hashtable->filename)
                return NULL;
            hashtable->hash = strdup(hash);
            if (!hashtable->hash)
                return NULL;
            hashtable->next = NULL;
        } else {
            current = hashtable;
            while (current->next != NULL)
                current = current->next;
            new_node = malloc(sizeof(hashtable_t));
            if (!new_node)
                return NULL;
            current->next = new_node;
        }
    }
    return hashtable;
}
