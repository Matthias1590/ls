#pragma once

#include <stddef.h>
#include <stdbool.h>

#ifdef _WIN32
#define MAX_FILE_NAME_LENGTH MAX_PATH
#else
#define MAX_FILE_NAME_LENGTH 4096
#endif

typedef enum {
    FT_DIRECTORY,
    FT_FILE,
} FileType;

typedef struct File {
    FileType type;
    char name[MAX_FILE_NAME_LENGTH];
    size_t size;
    struct File* next;
} File;

File* list_files_in_directory(const char* path);

bool directory_exists(const char* path);
