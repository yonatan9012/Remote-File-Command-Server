#ifndef COMMAND_EXECUTION_H
#define COMMAND_EXECUTION_H

#include <winsock2.h>

void execute_command(const char *operation, const char *fileName, const char *content,SOCKET connectedSocket);

#endif