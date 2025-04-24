/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** fim.c
*/

#include "../include/fim.h"

static void init_hashtable(hashtable_t *hashtable)
{
    hashtable->filename = NULL;
    hashtable->hash = NULL;
    hashtable->next = NULL;
}

static void free_hashtable(hashtable_t *hashtable)
{
    hashtable_t *current = NULL;
    hashtable_t *next = NULL;

    if (!hashtable)
        return;
    current = hashtable;
    while (current) {
        if (current->filename)
            free(current->filename);
        if (current->hash)
            free(current->hash);
        next = current->next;
        free(current);
        current = next;
    }
}

int main(int argc, char **argv)
{
    hashtable_t *hashtable = malloc(sizeof(hashtable_t));

    if (!hashtable)
        return 84;
    init_hashtable(hashtable);
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments.\n");
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(84);
    }
    store_file(hashtable, argc, argv);
    add_to_file(hashtable);
    free_hashtable(hashtable);
    return 0;
}
