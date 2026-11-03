#include <stdio.h>
#include <string.h>
#include "command_execution.h"
#include "file_handling.h"
#include "send_response.h"

void execute_command(const char *operation, const char *fileName, const char *content,SOCKET connectedSocket) {

    if (strcmp(operation, "CREATE") == 0) {
        handle_create(fileName, connectedSocket);
    }

    else if (strcmp(operation, "DELETE") == 0) {
        handle_delete(fileName,connectedSocket);
    }

    else if (strcmp(operation, "WRITE") == 0) {
        handle_write(fileName , content,connectedSocket);
    }

    else if (strcmp(operation, "APPEND") == 0) {
        handle_append(fileName , content,connectedSocket);
    }

    else if (strcmp(operation, "READ") == 0) {
        handle_read(fileName ,connectedSocket);
    }
    
}