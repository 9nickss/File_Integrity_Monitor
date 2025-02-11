/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** hashtable.c
*/

#include "../include/fim.h"
#include <stdio.h>
#include <stdlib.h>

hashtable_t *new_hashtable(int (*hash)(char *, int), int len)
{
    hashtable_t *ht = malloc(sizeof(hashtable_t));

    if (!ht)
        return NULL;
    ht->table = malloc(sizeof(node_t *) * len);
    if (!ht->table) {
        free(ht);
        return NULL;
    }
    for (int i = 0; i < len; i++)
        ht->table[i] = NULL;
    ht->size = len;
    return ht;
}

void delete_hashtable(hashtable_t *ht)
{
    node_t *current;
    node_t *next;

    if (!ht)
        return;
    for (int i = 0; i < ht->size; i++) {
        current = ht->table[i];
        while (current != NULL) {
            next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            current = next;
        }
    }
    free(ht->table);
    free(ht);
}