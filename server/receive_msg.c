#include <stdio.h>
#include "receive_msg.h"

void receive_message(SOCKET clientSocket) {
    char buffer[1024];
    while (1) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesReceived == 0) {
            printf("Client disconnected.\n");
            break;
        }
        if (bytesReceived == SOCKET_ERROR) {
            printf("Receive failed: %d\n", WSAGetLastError());
            break;
        }
        printf("Received %d bytes from client.\n", bytesReceived);
    }
}