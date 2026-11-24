
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "client_init.h"

int init_client(void) {

    int clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == -1) {
        perror("Socket creation failed");
        return -1;
    }

    struct sockaddr_in serverAddress = {0};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) != 1) {
        printf("Invalid IP address.\n");
        close(clientSocket);
        return -1;
    }

    if (connect(clientSocket,(struct sockaddr *)&serverAddress,sizeof(serverAddress)) == -1) {
        perror("Connection failed");
        close(clientSocket);
        return -1;
    }

    printf("Connected to server successfully.\n");

    return clientSocket;
}
