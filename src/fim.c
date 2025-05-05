/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** fim.c
*/

#include "../include/fim.h"

monitor_config_t *global_config = NULL;

static void lock_mutex_stop()
{
    if (global_config) {
        pthread_mutex_lock(&global_config->mutex);
        global_config->running = false;
        pthread_mutex_unlock(&global_config->mutex);
    }
}

static int init_structs(hashtable_t *hashtable, monitor_config_t *config)
{
    hashtable->filename = NULL;
    hashtable->hash = NULL;
    hashtable->next = NULL;
    config->hashtable = NULL;
    config->running = true;
    config->interval = 5;
    if (pthread_mutex_init(&config->mutex, NULL) != 0) {
        perror("Mutex init failed\n");
        return 84;
    }
    return 0;
}

void signal_handler(int sig)
{
    if (sig == SIGINT || sig == SIGTERM) {
        printf("\nReceived termination signal. Cleaning up...\n");
        lock_mutex_stop();
    }
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

static void helper(char *str)
{
    fprintf(stderr, "Wrong number of arguments.\n");
    fprintf(stderr, "Usage: %s <filename>\n", str);
    exit(84);
}

static void check_empty(char *input)
{
    if (fgets(input, INPUT_BUFFER_SIZE, stdin) == NULL) {
        if (feof(stdin)) {
            printf("\nExiting program...\n");
            lock_mutex_stop();
            return;
        }
        perror("Error reading input");
    }
}

static int get_file_nb()
{
    int nb = 0;

    if (!global_config->hashtable)
        return 0;
    hashtable_t *current = global_config->hashtable;

    if (!current)
        return 0;
    while (current) {
        if (current->filename)
            nb++;
        current = current->next;
    }
    return nb;
}

static void status_cmd()
{
    int nb_files = get_file_nb();

    printf("Currently monitoring %d files\n", nb_files);
    sleep(2);
    hashtable_t *current = global_config->hashtable;
    while (current) {
        printf("File monitored: %s\n", current->filename);
        current = current->next;
    }
}

static void check_cmd()
{
    int changes = 0;

    pthread_mutex_lock(&global_config->mutex);
    changes = check_changes(global_config->hashtable);
    pthread_mutex_unlock(&global_config->mutex);
    if (changes == 0)
        printf("No changes detected\n");
}

static void add_cmd(char *filename)
{
    store_file(global_config->hashtable, filename);
    add_to_file(global_config->hashtable);
}

void input_loop()
{
    char input[400];
    char command[400];
    char arg[300];

    printf("FIM> ");
    check_empty(input);
    input[strcspn(input, "\n")] = 0;
    if (sscanf(input, "%399s %299s", command, arg) >= 1) {
        if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0) {
            printf("Shutting down file monitor...\n");
            lock_mutex_stop();
            return;
        } else if (strcmp(command, "help") == 0)
            print_help();
        else if (strcmp(command, "status") == 0)
            status_cmd();
        else if (strcmp(command, "check") == 0)
            check_cmd();
        else if (strcmp(command, "add") == 0) {
            if (arg) {
                printf("Adding file: %s\n", arg);
                add_cmd(arg);
            } else
                printf("Please add file to add\n");
        } else
            printf("Unknown command. Type 'help' for a list of known commands\n");
    }
}

int main(void)
{
    hashtable_t *hashtable = malloc(sizeof(hashtable_t));
    monitor_config_t *config = malloc(sizeof(monitor_config_t));
    pthread_t monitor_thread;
    int thread_create_result;

    if (!hashtable || !config)
        return 84;
    if (init_structs(hashtable, config) == 84) {
        free_hashtable(hashtable);
        return 84;
    }
    config->hashtable = hashtable;
    load_from_file(&config->hashtable);
    thread_create_result = pthread_create(&monitor_thread, NULL, monitor_thread_function, config);
    if (thread_create_result != 0) {
        perror("Thread creation failed\n");
        return 84;
    }
    global_config = config;
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    while (global_config->running) {
        input_loop();
        usleep(10000);
    }
    //check_shutdown();
    pthread_join(monitor_thread, NULL);
    free_hashtable(hashtable);
    pthread_mutex_destroy(&config->mutex);
    return 0;
}
