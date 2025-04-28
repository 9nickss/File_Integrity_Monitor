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
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef FIM_H_
    #define FIM_H_

// file monitoring config
typedef struct monitor_config_s {
    hashtable_t *hashtable;
    int interval;
    bool running;
} monitor_config_t;

// hash list
typedef struct node_s {
    char *filename;
    char *hash;
    struct node_s *next;
} hashtable_t;

// store_file.c
int store_file(hashtable_t *hashtable, int argc, char **argv);

// hashtables.c
hashtable_t *add_to_hashtable(hashtable_t *hashtable, char *hash, char *filename);

// hash_file.c
int hash_filename(hashtable_t **hashtable, const char *filename);

// store_hash.c
int add_to_file(hashtable_t *hashtable);

#endif /*FIM_H_*/