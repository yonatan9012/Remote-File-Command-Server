#include <stdio.h>
#include <string.h>
#include "command_execution.h"
#include "file_handling.h"

int execute_command(const char *operation, const char *fileName, const char *content) {

    int result = 0;

    if (strcmp(operation, "CREATE") == 0) {
        result = handle_create(fileName);
    }

    else if (strcmp(operation, "DELETE") == 0) {
        result = handle_delete(fileName);
    }

    else if (strcmp(operation, "WRITE") == 0) {
        result = handle_write(fileName , content);
    }

    else if (strcmp(operation, "APPEND") == 0) {
        result = handle_append(fileName , content);
    }

    return result;
}