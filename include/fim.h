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
#include <signal.h>
#include <stdio.h>
#include <limits.h>

#ifndef FIM_H_
    #define FIM_H_
    #define INPUT_BUFFER_SIZE 400

// hash list
typedef struct node_s {
    char *filename;
    char *hash;
    struct node_s *next;
} hashtable_t;

// file monitoring config
typedef struct monitor_config_s {
    hashtable_t *hashtable;
    int interval;
    volatile bool running;
    pthread_mutex_t mutex;
} monitor_config_t;

// helpers.c
void print_help();

// store_file.c
int store_file(hashtable_t *hashtable, char *filename);
char *get_absolute_path(const char *filename);

// hashtables.c
hashtable_t *add_to_hashtable(hashtable_t *hashtable, char *hash, char *filename);

// hash_file.c
int hash_filename(hashtable_t **hashtable, const char *filename);
char *hash_file_content(const char *filename);

// store_hash.c
int add_to_file(hashtable_t *hashtable);
int load_from_file(hashtable_t **hashtable);

// check_file_hash.c
int check_changes(hashtable_t *hashtable);
void *monitor_thread_function(void *arg);

#endif /*FIM_H_*/
