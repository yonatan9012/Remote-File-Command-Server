
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "receive_msg.h"
#include "parsing.h"
#include "input_validation.h"
#include "send_response.h"

void receive_message(int connectedSocket) {
    char buffer[1024];
    char command[1024];
    size_t commandLength = 0;

    while (1) {
        ssize_t bytesReceived = recv(connectedSocket, buffer, sizeof(buffer), 0);

        if (bytesReceived == 0) {
            if (commandLength > 0) {
                printf("Client disconnected with an incomplete command.\n");
            } else {
                printf("Client disconnected.\n");
            }
            break;
        }

        if (bytesReceived == -1) {
            if (errno == EINTR) {
                continue;
            }

            perror("Receive failed");
            break;
        }

        printf("Received %zd bytes from client.\n", bytesReceived);

        for (ssize_t i = 0; i < bytesReceived; i++) {

            if (buffer[i] == '\0') {
                send_response(connectedSocket, "Error: Null byte detected in command.\n");
                return;
            }

            if (buffer[i] == '\n') {
                command[commandLength] = '\0';

                printf("Message receipt complete: %s\n", command);

                if (validate_input(command, connectedSocket)) {
                    parse_command(command, connectedSocket);
                }

                commandLength = 0;
            }
            else if (commandLength >= sizeof(command) - 1) {
                send_response(connectedSocket, "Error: Command too long.\n");
                return;
            }
            else {
                command[commandLength] = buffer[i];
                commandLength++;
            }
        }
    }
}
