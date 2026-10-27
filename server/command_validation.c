#include <stdio.h>
#include <string.h>
#include "command_validation.h"

void validate_command (const char *operation, const char *fileName, const char *content){
    const char *allowCommand [] = {
        "CREATE",
        "DELETE",
        "READ",
        "WRITE",
        "APPEND"
    };

    if ((strcmp(operation, "CREATE") == 0 ||strcmp(operation, "DELETE") == 0 || strcmp(operation, "READ") == 0) && (fileName[0] == '\0' || content[0] != '\0')) {
    printf("Error: Invalid CREATE, DELETE or READ arguments.\n");
    return;
    }

    if ((strcmp (operation, "WRITE")==0 || strcmp(operation, "APPEND")==0) && (fileName[0]=='\0' || content[0] =='\0')){
        printf("Error: Invalid WRITE or APPEND arguments.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i<5 ; i++){
        if(strcmp(operation, allowCommand[i])==0){
            found = 1;
            break;
        }
    }

    if (found == 0){
        printf("Error: Unknown command.\n");
        return;
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
            printf("Error: Content cannot be empty or contain only whitespace.\n");
            return;
        }
    }

    index = 0;
    while (fileName[index] != '\0'){
        if (fileName[index] == '\\' || fileName[index] == '/'){
            printf("Error: File name contains invalid path separators.\n");
            return;
        }
        index ++;
    }

    const char *invalidChars = "<>:\"/\\|?*";
    index =0;
    while (fileName[index] != '\0'){
        if (strchr(invalidChars, fileName[index])!=NULL){
            printf("Error: File name contains invalid characters.\n");
            return;
        }
        index ++;
    }

    char baseName [50];
    const char *reservedNames[] = {"CON","PRN","AUX","NUL","COM1","COM2","COM3","COM4","COM5",
    "COM6","COM7","COM8","COM9","LPT1","LPT2","LPT3","LPT4","LPT5","LPT6","LPT7","LPT8","LPT9"
    };

    index = 0;

    while (fileName[index] !='.' && fileName[index] !='\0'){
        baseName[index]=fileName[index];
        index ++;  
    }
    baseName[index] = '\0';


    for (int i = 0; i < 22; i++) {
        if (_stricmp(baseName, reservedNames[i]) == 0) {
            printf("Error: Reserved file name.\n");
            return;
        }
    } 
    
    index = 0;
    while (fileName[index] != '\0'){
        if((unsigned char)fileName[index] < 32 ){
            printf("Error: File name contains invalid control characters.\n");
            return;
        }
        index++;
    }

    index = 0;
    while (fileName[index] != '\0'){
        index ++;
    }
    index = index -1;
    if (fileName[index]==' ' || fileName[index]=='.'){
         printf("Error: File name.\n");
         return;
    }
}