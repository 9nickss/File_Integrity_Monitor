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
    monitor_config_t *config = get_config();
    hashtable_t *current = NULL;
    char *current_hash = NULL;

    if (!hashtable)
        return 84;
    current = hashtable;
    while (current != NULL) {
        if (current->filename)
            current_hash = hash_file_content(current->filename);
        if (!current_hash) {
            if (current->filename) {
                printf("Warning: %s not accessible.\n", current->filename);
                changed = 1;
            }
        }
        if (current->hash && strcmp(current->hash, current_hash) != 0) {
            printf("Alert: File hash changed: %s\n", current->filename);
            changed = 1;
            add_to_file(current);
            free(current->hash);
            current->hash = strdup(current_hash);
            if (!current->hash)
                break;
        }
        if (current->next)
            current = current->next;
        else
            break;
    }
    return changed;
}

void *monitor_thread_function(void *arg)
{
    monitor_config_t *config = (monitor_config_t *)arg;

    while (config->running) {
        pthread_mutex_lock(&config->mutex);
        check_changes(config->hashtable);
        pthread_mutex_unlock(&config->mutex);
        sleep(config->interval);
    }
    return NULL;
}
