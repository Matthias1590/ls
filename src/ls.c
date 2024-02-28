#include <stdio.h>

#include "fs.h"

char* consume_arg(int* argc, char*** argv) {
    if (*argc == 0) {
        return NULL;
    }

    char* arg = **argv;

    *argc -= 1;
    *argv += 1;

    return arg;
}

int main(int argc, char** argv) {
    consume_arg(&argc, &argv);  // skip program name

    char* path = consume_arg(&argc, &argv);
    if (path == NULL) {
        path = ".";
    }

    if (!directory_exists(path)) {  // todo: ls is able to handle files as well, we shouldnt assume the path is a directory
        printf("ls: cannot access '%s': No such file or directory\n", path);  // todo: this isnt entirely correct, ls escapes the path
        return 1;
    }

    File* files = list_files_in_directory(path);
    while (files != NULL) {
        printf("%s  ", files->name);
        files = files->next;
    }
    printf("\n");

    return 0;
}
