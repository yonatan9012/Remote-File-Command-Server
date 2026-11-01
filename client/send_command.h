#ifndef SEND_COMMAND_H
#define SEND_COMMAND_H

#include <winsock2.h>

int send_command(SOCKET clientSocket, const char *command);

#endif