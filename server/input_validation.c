#include <stdio.h>
#include "input_validation.h"
#include "send_response.h"

int validate_input(const char *command, SOCKET connectedSocket) {
    int hasContent = 0;

    if (command[0] == '\0') {
        send_response(connectedSocket, "Error: Invalid input.\n");
        printf("Error: Invalid input.\n");
        return 0;
    }

    for (int i = 0; command[i] != '\0'; i++) {

        if ((unsigned char)command[i] < 32 && command[i] != '\t') {
                send_response(connectedSocket, "Error: Invalid input.\n");
                return 0;
            }

        if (command[i] != ' ' && command[i] != '\t') {
            hasContent = 1;
        }
    }

    if (hasContent == 0) {
        send_response(connectedSocket, "Error: Invalid input.\n");
        return 0;
    }

    return 1;
}