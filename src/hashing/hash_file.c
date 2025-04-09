/*
** 9nickss, 2025
** File_Integrity_Monitor
** File description:
** hash_file.c
*/

#include "../../include/fim.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>


char *separate_name(char *filename)
{
    char *str = strdup(filename);
    char *last_slash = strrchr(str, "/");

    if (last_slash != NULL)
        return strdup(last_slash + 1);
    return str;
}

void hash_filename(char *filename)
{
    char *name = NULL;

    name = separate_name(filename);

}
