#include <stdio.h>
#include "client_init.h"

int main(void) {
    SOCKET clientSocket = init_client();

    if (clientSocket == INVALID_SOCKET) {
        printf("Error: Client initialization failed.\n");
        return 1;
    }

    printf("Client connected successfully.\n");
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}