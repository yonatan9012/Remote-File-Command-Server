#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stddef.h>
#include <winsock2.h>

int build_file_path(const char *filename, char *fullPath, size_t fullPathSize);

int handle_create(const char *filename,SOCKET connectedSocket);
int handle_write(const char *filename, const char *content,SOCKET connectedSocket);
int handle_append(const char *filename, const char *content,SOCKET connectedSocket);
int handle_delete(const char *filename,SOCKET connectedSocket);
int handle_read(const char *filename, SOCKET connectedSocket );

#endif