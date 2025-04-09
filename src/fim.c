/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** fim.c
*/

#include "../include/fim.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments.\n");
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(84);
    }
    store_file(argc, argv);
    return 0;
}
