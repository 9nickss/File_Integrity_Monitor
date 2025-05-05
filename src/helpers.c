/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** helpers.c
*/

#include "../include/fim.h"

void print_help()
{
    printf("Availbale commands:\n");
    printf("  help          - Show this help message\n");
    printf("  status        - Show status of monitored files\n");
    printf("  add <file>    - Add a new file to be monitored\n");
    printf("  chec          - Force check on monitored files\n");
    printf("  exit/quit     - Exit the program\n");
}
