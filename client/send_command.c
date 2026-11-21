
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "send_command.h"

int send_command(int clientSocket, const char *command) {
    size_t totalSent = 0;
    size_t commandLength = strlen(command);

    while (totalSent < commandLength) {
        ssize_t status = send(clientSocket,
                              command + totalSent,
                              commandLength - totalSent,
                              MSG_NOSIGNAL);

        if (status == -1) {
            if (errno == EINTR) {
                continue;
            }

            perror("Error: Cannot send command");
            return 0;
        }

        if (status == 0) {
            printf("Error: No data was sent.\n");
            return 0;
        }

        totalSent += (size_t)status;
    }

    return 1;
}
