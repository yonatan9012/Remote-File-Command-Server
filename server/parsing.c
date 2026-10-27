#include <stdio.h>
#include "parsing.h"
#include "command_validation.h"

void parse_command(const char *command) {
    char operation[10];
    char fileName[50];
    char content[1024];
    int index = 0;
    int count = 0;
    while (command[index] != '\0') {
        if (command[index] == ' ') {
            index++;
            break;
        }

        if (count >= sizeof(operation) - 1) {
            printf("Parsing Error: Command name exceeds the maximum allowed length.\n");
            return;
        }

        operation[count] = command[index];
        index++;
        count++;
    }
    operation[count] = '\0';
    count = 0;



    while (command[index]==' '){
        index ++;
    }
    

    while (command[index] != '\0') {
        if (command[index] == ' ') {
            index++;
            break;
        }
        if (count >= sizeof(fileName) - 1) {
            printf("Parsing Error: File name exceeds the maximum allowed length.\n");
            return;
        }
        fileName[count] = command[index];
        index++;
        count++;
    }
    fileName[count] = '\0';
    count = 0;

    while (command[index] != '\0') {

        if (count >= sizeof(content) - 1) {
            printf("Parsing Error: Content exceeds the maximum allowed length.\n");
            return;
        }
        content[count] = command[index];
        index++;
        count++;
    }
    content[count] = '\0';

    validate_command(operation, fileName, content);
}