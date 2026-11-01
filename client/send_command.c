#include <stdio.h>
#include <string.h>
#include "send_command.h"

int send_command(SOCKET clientSocket, const char *command){
    int totalSent = 0;
    int commandLength = strlen(command);

    while (totalSent < commandLength){
        int status = send(clientSocket, command + totalSent, commandLength - totalSent, 0); 

        if (status <= 0){
            printf("Error: Cannot send command.\n");
            return 0;
        }

        totalSent = status + totalSent;
    }
    return 1;
}