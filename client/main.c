#include <stdio.h>
#include "client_init.h"
#include "send_command.h"

int main(void) {
    SOCKET clientSocket = init_client();
    char inputclient [1024];

    if (clientSocket == INVALID_SOCKET) {
        printf("Error: Client initialization failed.\n");
        return 1;
    }
    printf("Client connected successfully.\n");

    while(1){
        printf("Enter command: ");
        if (fgets(inputclient, sizeof(inputclient), stdin) == NULL) {
        printf("Error: Cannot read input.\n");
        break;
        }

        if (send_command(clientSocket, inputclient) == 0) {
        printf("Error: Cannot send command.\n");
        break;
        }
    }
   
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}