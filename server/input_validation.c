#include <stdio.h>
#include "input_validation.h"

int validate_input(const char *command) {
    int hasContent = 0;

    if (command[0] == '\0') {
        printf("Error: Invalid input.\n");
        return 0;
    }

    for (int i = 0; command[i] != '\0'; i++) {

        if (command[i] == '\r' || 
            (unsigned char)command[i] < 32 && 
            command[i] != '\t') {
            printf("Error: Invalid input.\n");
            return 0;
        }

        if (command[i] != ' ' && command[i] != '\t') {
            hasContent = 1;
        }
    }

    if (hasContent == 0) {
        printf("Error: Invalid input.\n");
        return 0;
    }

    return 1;
}






    /* 
    $client = [System.Net.Sockets.TcpClient]::new("127.0.0.1", 8080)
$writer = [System.IO.StreamWriter]::new($client.GetStream())
$writer.AutoFlush = $true
$writer.WriteLine("CREATE test.txt")
$writer.Dispose()
$client.Close()
    
    */