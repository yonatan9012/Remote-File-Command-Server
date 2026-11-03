#include <stdio.h>
#include "receive_response.h"

int receive_response(SOCKET clientSocket) {
    char buffer[1024];
    size_t index = 0;

    while (1) {

        if (index >= sizeof(buffer) - 1) {
            buffer[index] = '\0';
            printf("%s", buffer);
            index = 0;
        }

        int bytesReceived = recv(clientSocket, &buffer[index], 1, 0);

        if (bytesReceived == 0) {
            printf("Error: Server disconnected!\n");
            return 0;
        }

        if (bytesReceived == SOCKET_ERROR) {
            printf("Error: Cannot receive response from server!\n");
            return 0;
        }

        if (buffer[index] == '\n') {
            buffer[index] = '\0';
            printf("%s\n", buffer);
            return 1;
        }

        index++;
    }

}
           