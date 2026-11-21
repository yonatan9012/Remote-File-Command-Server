
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "send_response.h"

int send_response(int connectedSocket, const char *message) {
    size_t totalSent = 0;
    size_t commandLength = strlen(message);

    while (totalSent < commandLength) {
        ssize_t status = send(connectedSocket,
                              message + totalSent,
                              commandLength - totalSent,
                              MSG_NOSIGNAL);

        if (status == -1) {
            if (errno == EINTR) {
                continue;
            }

            perror("Error: Cannot send response");
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
