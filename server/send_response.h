#ifndef SEND_RESPONSE_H
#define SEND_RESPONSE_H

#include <winsock2.h>

int send_response(SOCKET connectedSocket, const char *message);

#endif