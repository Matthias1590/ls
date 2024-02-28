#include "fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef _WIN32
#define LINUX
#endif

#ifdef _WIN32
#include <windows.h>
#elif defined LINUX
#define __USE_MISC
#include <dirent.h>
#else
#error "Unsupported platform"
#endif

static File* create_file(File* previous_file) {
    File* new_file = calloc(1, sizeof(File));
    new_file->next = NULL;

    if (previous_file) {
        previous_file->next = new_file;
    }

    return new_file;
}

File* list_files_in_directory(const char* path) {
#ifdef LINUX
    DIR* dir = opendir(path);
    if (dir == NULL) {
        return NULL;
    }

    File* files = NULL;
    File* last_file = NULL;

    while (true) {
        struct dirent* entry = readdir(dir);
        if (entry == NULL) {
            break;
        }

        last_file = create_file(last_file);
        if (files == NULL) {
            files = last_file;
        }

        last_file->type = entry->d_type == DT_DIR ? FT_DIRECTORY : FT_FILE;
        memcpy(&last_file->name, entry->d_name, strlen(entry->d_name) + 1);
        last_file->size = entry->d_reclen;
    }

    closedir(dir);
    return files;
#else
#error "Unsupported platform"
#endif
}

bool directory_exists(const char* path) {
#ifdef LINUX
    DIR* dir = opendir(path);
    if (dir == NULL) {
        return false;
    }

    closedir(dir);
    return true;
#else
#error "Unsupported platform"
#endif
}
