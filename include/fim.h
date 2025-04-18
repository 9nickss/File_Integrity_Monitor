/*
** 9nickss
** File_Integrity_Monitor
** File description:
** fim.h
*/

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <openssl/sha.h>

#ifndef FIM_H_
    #define FIM_H_

typedef struct node_s {
    char *key;
    char *value;
    struct node_s *next;
} node_t;

typedef struct hashtable_s {
    node_t **table;
    int size;
} hashtable_t;

// sore_file.c
int store_file(int argc, char **argv);

// hashtable.c
hashtable_t *new_hashtable(int (*hash)(char *, int), int len);
void delete_hashtable(hashtable_t *ht);

// hash_file.c
void hash_filename(const char *filename);

#endif /*FIM_H_*/