/*
** 9nickss
** File_Integrity_Monitor
** File description:
** fim.h
*/

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

int store_file(int argc, char **argv);
hashtable_t *new_hashtable(int (*hash)(char *, int), int len);

#endif /*FIM_H_*/