#include <stdio.h>
#include <string.h>
#include "command_validation.h"
#include "command_execution.h"
#include "send_response.h"

int validate_command (const char *operation, const char *fileName, const char *content,SOCKET connectedSocket){
    const char *allowCommand [] = {
        "CREATE",
        "DELETE",
        "READ",
        "WRITE",
        "APPEND"
    };

    if ((strcmp(operation, "CREATE") == 0 ||strcmp(operation, "DELETE") == 0 || strcmp(operation, "READ") == 0) && (fileName[0] == '\0' || content[0] != '\0')) {
        send_response(connectedSocket, "Error: Invalid CREATE, DELETE or READ arguments.\n");
        return -1;
    }

    if ((strcmp (operation, "WRITE")==0 || strcmp(operation, "APPEND")==0) && (fileName[0]=='\0' || content[0] =='\0')){
        send_response(connectedSocket, "Error: Invalid WRITE or APPEND arguments.\n");
        return -1;
    }

    int found = 0;
    for (int i = 0; i<5 ; i++){
        if(strcmp(operation, allowCommand[i])==0){
            found = 1;
            break;
        }
    }

    if (found == 0){
        send_response(connectedSocket, "Error: Unknown command.\n");
        return -1;
    }

        int index = 0;
        int hasText = 0;
        if ((strcmp (operation, "WRITE")==0 || strcmp(operation, "APPEND")==0)){
        while (content[index] != '\0'){
            if(content[index] !=' ' && content[index]!='\t'){
                hasText = 1;
                break;
            }
            index ++;
        }
        if(hasText==0){
            send_response(connectedSocket, "Error: Content cannot be empty or contain only whitespace.\n");
            return -1;
        }
    }

    const char *invalidChars = "<>:\"/\\|?*";
    index =0;
    while (fileName[index] != '\0'){
        if (strchr(invalidChars, fileName[index])!=NULL){
            send_response(connectedSocket, "Error: File name contains invalid characters.\n");
            return -1;
        }
        index ++;
    }

    char baseName [50];
    const char *reservedNames[] = {"CON","PRN","AUX","NUL","COM1","COM2","COM3","COM4","COM5",
    "COM6","COM7","COM8","COM9","LPT1","LPT2","LPT3","LPT4","LPT5","LPT6","LPT7","LPT8","LPT9"
    };

    if (fileName[0] == '\0') {
        send_response(connectedSocket, "Error: File name is required.\n");
        return -1;
    }

    index = 0;

    while (fileName[index] !='.' && fileName[index] !='\0'){
        baseName[index]=fileName[index];
        index ++;  
    }
    baseName[index] = '\0';


    for (int i = 0; i < 22; i++) {
        if (_stricmp(baseName, reservedNames[i]) == 0) {
            send_response(connectedSocket, "Error: Reserved file name.\n");
            return -1;
        }
    } 
    
    index = 0;
    while (fileName[index] != '\0'){
        if((unsigned char)fileName[index] < 32 ){
            send_response(connectedSocket, "Error: File name contains invalid control characters.\n");
            return -1;
        }
        index++;
    }

    index = 0;
    while (fileName[index] != '\0'){
        index ++;
    }
    index = index -1;
    if (fileName[index]==' ' || fileName[index]=='.'){
        send_response(connectedSocket, "Error: File name.\n");
        return -1;
    }

    execute_command(operation, fileName, content, connectedSocket);
    return 1;
}