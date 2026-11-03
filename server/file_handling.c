#include <stdio.h>
#include <string.h>
#include <io.h>
#include "server_init.h"
#include "file_handling.h"
#include "send_response.h"

int build_file_path(const char *filename, char *fullPath, size_t fullPathSize) {

    if (filename == NULL || fullPath == NULL || fullPathSize == 0) {
        return 0;
    }
    
    if (filename[0] == '\0' ||
        strcmp(filename, ".") == 0 ||
        strcmp(filename, "..") == 0 ||
        strchr(filename, '/') != NULL ||
        strchr(filename, '\\') != NULL ||
        strchr(filename, ':') != NULL) {
        return 0;
    }

    int result = snprintf(fullPath, fullPathSize, "%s\\%s", SERVER_DIRECTORY, filename);
    if (result < 0 || (size_t)result >= fullPathSize) {
        return 0;
    }
    return 1;
}   

int handle_create(const char *filename, SOCKET connectedSocket) {
    char path[500];

    if (build_file_path(filename, path, sizeof(path)) == 0) {
        send_response(connectedSocket,"Error: Failed to build file path.\n");
        return 0;
    }

    FILE *file = fopen(path, "wx");

    if (file == NULL) {
        send_response(connectedSocket,"Error: Failed to create file.\n");
        return 0;
    } 

    if (fclose(file) != 0) {
        send_response(connectedSocket,"Error: Failed to close file.\n");
        return 0;
    }
    
    send_response(connectedSocket, "File created successfully.\n");
    return 1;
}


int handle_write(const char *filename, const char *content,SOCKET connectedSocket) {
    char path1[1200];

    if (build_file_path(filename, path1, sizeof(path1)) == 0) {
        send_response(connectedSocket, "Error: Cannot build file path.\n");
        return 0;
    }

    FILE *file = fopen(path1, "r+");

    if (file == NULL) {
        send_response(connectedSocket, "Error: Cannot open file.\n");
        return 0;
    }

    int fd = _fileno(file);
    if (fd == -1){
        send_response(connectedSocket, "Error: Cannot get file descriptor.\n");
        fclose(file);
        return 0;
    }
    if(_chsize_s(fd, 0) != 0){
        send_response(connectedSocket, "Error: Cannot clear file.\n");
        fclose(file);
        return 0;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        send_response(connectedSocket, "Error: Cannot set file position.\n");
        fclose(file);
        return 0;
    }

    size_t a = fwrite(content, 1, strlen(content), file);

    if (strlen(content) != a) {
        send_response(connectedSocket, "Error: Cannot write to file.\n");
        fclose(file);
        return 0;
    }

    if (fclose(file) != 0) {
        send_response(connectedSocket, "Error: Cannot close file.\n");
        return 0;
    }
    send_response(connectedSocket,"File written successfully.\n");
    return 1;
}


int handle_append (const char *filename, const char *content,SOCKET connectedSocket){
    char path2 [1200];
    if (build_file_path(filename, path2, sizeof(path2)) == 0) {
        send_response(connectedSocket, "Error: Cannot build file path.\n");
        return 0;
    }

    FILE *file = fopen(path2, "r+");

     if (file == NULL) {
        send_response(connectedSocket, "Error: Cannot open file.\n");
        return 0;
    }

    if(fseek(file, 0, SEEK_END)!=0){
        send_response(connectedSocket, "Error: Cannot move to end of file.\n");
        fclose(file);
        return 0;
    }

    size_t a = fwrite(content, 1, strlen(content), file);
    if (strlen(content) != a) {
        send_response(connectedSocket, "Error: Cannot append to file.\n");
        fclose(file);
        return 0;
    }

    if (fclose(file) != 0) {
        send_response(connectedSocket, "Error: Cannot close file.\n");
        return 0;
    }
    send_response(connectedSocket,"Content added successfully.\n");
    return 1;
}


int handle_delete (const char *filename,SOCKET connectedSocket){
    char path_delete [500];

    if (build_file_path(filename, path_delete, sizeof(path_delete)) == 0) {
        send_response(connectedSocket, "Error: Cannot build file path.\n");
        return 0;
    }
    if ( remove(path_delete) !=0 ){
        send_response(connectedSocket, "Error: Cannot delete file.\n");
        return 0;
    } 
    send_response(connectedSocket,"File deleted successfully.\n");
    return 1;
}

int handle_read(const char *filename, SOCKET connectedSocket ){
    char buffer [1024];
    char path_read [1024];
    if (build_file_path(filename, path_read, sizeof(path_read))==0){
        send_response(connectedSocket, "Error: Cannot build file path.\n");
        return 0;
    }

    FILE *file = fopen(path_read,"rb");

    if(file==NULL){
        send_response(connectedSocket, "Error: Cannot open file.\n");
        return 0;
    }

    size_t bytesRead = fread(buffer, 1, sizeof(buffer) -2 , file);
    buffer[bytesRead] = '\n';
    buffer[bytesRead + 1] = '\0';

    if (ferror(file) != 0) {
        send_response(connectedSocket,"Error reading the file.\n");
        fclose(file);
        return 0;
    }

    if (ferror(file) == 0 && bytesRead == 0) {
        send_response(connectedSocket, "ERROR: No text to read.\n");
        fclose(file);
        return 0;
    }

    if (fclose(file) != 0) {
        send_response(connectedSocket, "Error: Cannot close file.\n");
        return 0;
    }

    send_response(connectedSocket, buffer);
    return 1;
}