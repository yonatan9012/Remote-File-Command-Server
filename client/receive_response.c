#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "receive_response.h"

int receive_response(int clientSocket) {
    char buffer[1024];
    size_t index = 0;

    while (1) {
        if (index >= sizeof(buffer) - 1) {
            buffer[index] = '\0';
            printf("%s", buffer);
            index = 0;
        }

        ssize_t bytesReceived = recv(clientSocket, &buffer[index], 1, 0);

        if (bytesReceived == 0) {
            printf("Error: Server disconnected!\n");
            return 1;
        }

        if (bytesReceived == -1) {
            perror("Error: Cannot receive response from server");
            return 1;
        }

        if (buffer[index] == '\n') {
            buffer[index] = '\0';
            printf("%s\n", buffer);
            return 0;
        }

        index++;
    }
}
