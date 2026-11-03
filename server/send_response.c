#include <stdio.h>
#include <string.h>
#include "send_response.h"

int send_response(SOCKET connectedSocket, const char *message){
    int totalSent = 0;
    int commandLength = strlen(message);

    while (totalSent < commandLength){
        int status = send(connectedSocket, message + totalSent, commandLength - totalSent, 0); 

        if (status <= 0){
            printf("Error: Cannot send response.\n");
            return 0;
        }

        totalSent = status + totalSent;
    }
    return 1;

}