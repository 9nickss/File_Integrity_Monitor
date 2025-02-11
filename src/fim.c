#include <stdlib.h>

char *get_file(int argc, char **argv)
{
    char *file = NULL;

    if (!argv[1]) {
        perror("Invalid argument.");
        exit(84);
    }
    file = argv[1];
    return file;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        perror("Wrong number of arguments.");
        exit(84);
    }
    get_file(argc, argv);
    return 0;
}
