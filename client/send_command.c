
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "send_command.h"

int send_command(int clientSocket, const char *command) {
    size_t totalSend = 0; // סופר את התווים שנשלחו
    size_t commandLength = strlen(command); // מחזיר את אורך המחרוזת 

    while (totalSend < commandLength) {
        ssize_t status = send(clientSocket, command + totalSend ,commandLength - totalSend, 0);

        if (status == -1) {
            perror("Error: Cannot send command");
            return 1;
        }

        if (status == 0) {
            printf("Error: No data was sent.\n");
            return 1;
        }

        totalSend += status;
    }

    return 0;
}
