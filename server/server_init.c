
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "server_init.h"
#include "receive_msg.h"


int create_directory(void) {
    const char *path = SERVER_DIRECTORY;

    struct stat info;
    int result = stat(path, &info);

    if (result == 0) {
        if (S_ISDIR(info.st_mode)) {
            printf("The server's working directory already exists.\n");
            return 1;
        }
        else {
            printf("Error: The path exists but is not a directory.\n");
            return 0;
        }
    }

    if (errno != ENOENT) {
        perror("Failed to check the server's working directory");
        return 0;
    }

    int mkdirResult = mkdir(path, 0755);

    if (mkdirResult == 0) {
        printf("Directory created successfully.\n");
        return 1;
    }

    perror("Failed to create the server's working directory");
    return 0;
}


void start_server(void) {

    int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocket == -1) {
        perror("Socket creation failed");
        return;
    }

    printf("Socket to server created successfully.\n");

    struct sockaddr_in serverAddress = {0};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1",
                  &serverAddress.sin_addr) != 1) {
        printf("Invalid IP address or conversion failed.\n");
        close(serverSocket);
        return;
    }

    if (bind(serverSocket,
             (struct sockaddr *)&serverAddress,
             sizeof(serverAddress)) == -1) {

        perror("Bind failed");
        close(serverSocket);
        return;
    }

    if (listen(serverSocket, 5) == -1) {
        perror("Listen failed");
        close(serverSocket);
        return;
    }

    printf("Server is listening on port 8080...\n");

    while (1) {

        int connectedSocket = accept(serverSocket, NULL, NULL);

        if (connectedSocket == -1) {
            if (errno == EINTR) {
                continue;
            }

            perror("Accept failed");
            close(serverSocket);
            return;
        }

        receive_message(connectedSocket);

        close(connectedSocket);
    }
}
