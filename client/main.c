#include <stdio.h>
#include <string.h>
#include "client_init.h"
#include "send_command.h"
#include "receive_response.h"

int main(void) {
    SOCKET clientSocket = init_client();
    char inputclient [1024];
    int status = 0;

    if (clientSocket == INVALID_SOCKET) {
        printf("Error: Client initialization failed.\n");
        return 1;
    }
    printf("Client connected successfully.\n");

    while(1){
        printf("Enter command: ");

        if (fgets(inputclient, sizeof(inputclient), stdin) == NULL) {
            printf("Error: Cannot read input.\n");
            status = 1;
            break;
        }

        if (strcmp(inputclient, "EXIT\n") == 0) {
            printf("EXIT successfully\n");
            status = 0;
            break;
        }

        if (send_command(clientSocket, inputclient) == 0) {
            printf("Error: Cannot send command.\n");
            status = 1;
            break;
        }
    
        if (receive_response(clientSocket) == 0) {
            status = 1;
            break;
        }
    
    }
   
    closesocket(clientSocket);
    WSACleanup();
    return status;
}