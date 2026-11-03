#ifndef COMMAND_VALIDATION_H
#define COMMAND_VALIDATION_H

#include <winsock2.h>

int validate_command(const char *operation,const char *fileName,const char *content,SOCKET connectedSocket);

#endif