#include <stdio.h>
#include "receive_msg.h"
#include "parsing.h"
#include "input_validation.h"

void receive_message(SOCKET clientSocket) {
    char buffer[1024];
    char command[1024];
    int commandLength = 0;

    while (1) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesReceived == 0) {
            if (commandLength > 0) {
                printf("Error: Incomplete command received.\n");
            } else {
                printf("Client disconnected.\n");
            }
            break;
        }

        if (bytesReceived == SOCKET_ERROR) {
            printf("Receive failed: %d\n", WSAGetLastError());
            break;
        }

        printf("Received %d bytes from client.\n", bytesReceived);

        for (int i = 0; i < bytesReceived; i++) {

            if (buffer[i] == '\0') {
                printf("Error: Null byte detected in command.\n");
                return;
            }

            if (buffer[i] == '\n') {
                command[commandLength] = '\0';

                printf("Message receipt complete: %s\n", command);

                if (validate_input(command)) {
                    parse_command(command);
                }

                commandLength = 0;
            }
            else if (commandLength >= (int)sizeof(command) - 1) {
                printf("Error: Command too long.\n");
                return;
            }
            else {
                command[commandLength] = buffer[i];
                commandLength++;
            }
        }
    }
}