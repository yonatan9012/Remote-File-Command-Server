#include <stdio.h>
#include "server_init.h"

int main(void) {
    if(create_directory() == 1) {
        printf("Error: Server initialization failed.\n");
        return 1;
    }
    
    start_server();
    
    return 0;
}

