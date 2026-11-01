#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stddef.h>

int build_file_path(const char *filename, char *fullPath, size_t fullPathSize);
void handle_create(const char *filename);
void handle_write(const char *filename, const char *content);

#endif
