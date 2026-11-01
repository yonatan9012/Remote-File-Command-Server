#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stddef.h>

int build_file_path(const char *filename, char *fullPath, size_t fullPathSize);

int handle_create(const char *filename);
int handle_write(const char *filename, const char *content);
int handle_append(const char *filename, const char *content);
int handle_delete(const char *filename);

#endif