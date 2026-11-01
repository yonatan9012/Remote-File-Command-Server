#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "client_init.h"

SOCKET init_client(void) {
    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
        return INVALID_SOCKET;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return INVALID_SOCKET;
    }

    printf("Client socket created successfully.\n");

    struct sockaddr_in serverAddress = {0};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    if (InetPtonA(AF_INET, "127.0.0.1", &serverAddress.sin_addr) != 1) {
        printf("Invalid IP address.\n");
        closesocket(clientSocket);
        WSACleanup();
        return INVALID_SOCKET;
    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddress,
                sizeof(serverAddress)) == SOCKET_ERROR) {
        printf("Connection failed: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return INVALID_SOCKET;
    }

    printf("Connected to server successfully.\n");

    return clientSocket;
}
