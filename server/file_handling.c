#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "server_init.h"
#include "file_handling.h"
#include "send_response.h"


int build_file_path(const char *filename, char *fullPath, size_t fullPathSize) {

    if (filename == NULL || fullPath == NULL || fullPathSize == 0) {
        return 1;
    }
    if (strcmp(filename, ".") == 0 ||strcmp(filename, "..") == 0) {
        printf("Error: Invalid file name.\n");
        return 1;
    }

    int result = snprintf(fullPath, fullPathSize, "%s/%s", SERVER_DIRECTORY, filename);//נשמר מספר התווים שהיא כתבה ם

    if (result < 0 || (size_t)result >= fullPathSize) {
        return 1;
    }

    return 0;
}


int handle_create(const char *filename, int connectedSocket) {
    char path[500];

    if (build_file_path(filename, path, sizeof(path)) != 0) {
        send_response(connectedSocket, "Error: Failed to build file path.\n");
        return 1;
    }

    FILE *file = fopen(path, "wx");

    if (file == NULL) {
        send_response(connectedSocket, "Error: Failed to create file.\n");
        return 1;
    }

    if (fclose(file) != 0) {
        send_response(connectedSocket, "Error: Failed to close file.\n");
        return 1;
    }

    send_response(connectedSocket, "File created successfully.\n");
    return 0;
}

int handle_write(const char *filename, const char *content, int connectedSocket) {
    char path1[1200];

    if (build_file_path(filename, path1, sizeof(path1)) != 0) {
        send_response(connectedSocket, "Error: Invalid path.\n");
        return 1;
    }

    FILE *file = fopen(path1, "r"); //קריאה בלבד הקובץ חייב להיות קיים

    if (file == NULL) {
        send_response(connectedSocket, "Error: File not found or cannot open.\n");
        return 1;
    }
    fclose(file);

    file = fopen(path1, "w"); //כתיבה מוחק את התוכן של קובץ קיים

    if (file == NULL) {
        send_response(connectedSocket, "Error: Cannot open file.\n");
        return 1;
    }

    size_t bytes = fwrite(content, 1, strlen(content), file);

    if (bytes != strlen(content)) {
        send_response(connectedSocket, "Error: Cannot write file.\n");
        fclose(file);
        return 1;
    }

    if (fclose(file) != 0) {
        send_response(connectedSocket, "Error: Cannot close file.\n");
        return 1;
    }

    send_response(connectedSocket, "File written successfully.\n");
    return 0;
}

int handle_append(const char *filename, const char *content, int connectedSocket) {
    char path2[1200];

    if (build_file_path(filename, path2, sizeof(path2)) != 0) {
        send_response(connectedSocket, "Error: Cannot build file path.\n");
        return 1;
    }

    FILE *file = fopen(path2, "r"); //קריאה בלבד הקובץ חייב להיות קיים
    if (file == NULL) {
        send_response(connectedSocket, "Error: File not found or cannot open.\n");
        return 1;
    }
    fclose(file);

    
    file = fopen(path2, "a"); // כתיבה בסוף הקובץ

    if (file == NULL) {
        send_response(connectedSocket, "Error: Cannot open file.\n");
        return 1;
    }

    size_t a = fwrite(content, 1, strlen(content), file);

    if (a != strlen(content)) {
        send_response(connectedSocket, "Error: Cannot append to file.\n");
        fclose(file);
        return 1;
    }

    if (fclose(file) != 0) {
        send_response(connectedSocket, "Error: Cannot close file.\n");
        return 1;
    }

    send_response(connectedSocket, "Content added successfully.\n");
    return 0;
}

int handle_delete(const char *filename, int connectedSocket) {
    char path_delete[500];

    if (build_file_path(filename, path_delete, sizeof(path_delete)) != 0) {
        send_response(connectedSocket, "Error: Cannot build file path.\n");
        return 1;
    }

    if (unlink(path_delete) != 0) {
        send_response(connectedSocket, "Error: Cannot delete file.\n");
        return 1;
    }

    send_response(connectedSocket, "File deleted successfully.\n");
    return 0;
}


int handle_read(const char *filename, int connectedSocket) {
    char buffer[1024];
    char path_read[1024];

    if (build_file_path(filename, path_read, sizeof(path_read)) != 0) {
        send_response(connectedSocket, "Error: Cannot build file path.\n");
        return 1;
    }

    FILE *file = fopen(path_read, "r"); // קריאה-חייב להיות קיים

    if (file == NULL) {
        send_response(connectedSocket, "Error: Cannot open file.\n");
        return 1;
    }

    size_t bytesRead;
    size_t totalBytesRead = 0;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer) - 1, file)) > 0) {

        buffer[bytesRead] = '\0';

        if (send_response(connectedSocket, buffer) != 0) {
            fclose(file);
            return 1;
        }

        totalBytesRead += bytesRead;
    }

    if (ferror(file)) {
        fclose(file);
        send_response(connectedSocket, "\n");
        return 1;
    }

    if (fclose(file) != 0) {
        send_response(connectedSocket, "\n");
        return 1;
    }

    if (totalBytesRead == 0) {
        send_response(connectedSocket, "ERROR: No text to read.\n");
        return 1;
    }

    if (send_response(connectedSocket, "\n") != 0) {
        return 1;
    }

    return 0;
}
