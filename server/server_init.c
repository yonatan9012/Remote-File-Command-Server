#include <stdio.h>
#include <direct.h>
#include <sys/stat.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "server_init.h"
#include "receive_msg.h"

void start_server(void) {

WSADATA wsaData;
int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

if (result != 0) {
    printf("WSAStartup failed: %d\n", result);
    return;
}

SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

if (serverSocket == INVALID_SOCKET) {
    printf("Socket creation failed: %d\n", WSAGetLastError());
    WSACleanup();
    return;
}
printf("Socket created successfully.\n");

struct sockaddr_in serverAddress={0};
serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(8080);
 if(InetPtonA(AF_INET, "127.0.0.1", &serverAddress.sin_addr)!=1){
    printf("Invalid IP address or conversion failed.\n");
    closesocket(serverSocket);
    WSACleanup();
    return;
}

if(bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress))== SOCKET_ERROR){
    printf("Bind failed: %d\n", WSAGetLastError());
    closesocket(serverSocket);
    WSACleanup();
    return;
}

if(listen(serverSocket,5)==SOCKET_ERROR){
     printf("listen failed: %d\n", WSAGetLastError());
     closesocket(serverSocket);
     WSACleanup();
     return;
}

printf("Server is listening on port 8080...\n");

while (1) {
    SOCKET clientSocket = accept (serverSocket , NULL , NULL);
    if(clientSocket==INVALID_SOCKET){
        printf("accept filed: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return;
        }
        receive_message(clientSocket);
         closesocket(clientSocket);
    }
}

void create_directory(void){
    struct _stat info;
    int result = _stat("C:\\Users\\User\\Desktop\\filename", &info);
    if (result == 0 && (info.st_mode & _S_IFDIR )){
        printf("The server's working directory already exists.\n");
    }
    else {
    int a = _mkdir ("C:\\Users\\User\\Desktop\\filename");
        if(a==0){  
            printf("Directory created successfully\n");
        }
        else{
            printf("Error: Failed to create the server's working directory.\n");
        }
    }
}