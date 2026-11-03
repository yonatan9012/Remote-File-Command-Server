#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <winsock2.h>

int validate_input(const char *command, SOCKET connectedSocket);

#endif