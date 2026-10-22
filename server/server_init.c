#include <stdio.h>
#include <direct.h>
#include <sys/stat.h>
#include "server_init.h"

void start_server(void) {
    printf("Server is running...\n");
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