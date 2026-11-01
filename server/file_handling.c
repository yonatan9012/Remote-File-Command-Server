#include <stdio.h>
#include <string.h>
#include "server_init.h"
#include "file_handling.h"

void validate_filename(){

     /*לבדוק האם לעשות את כל הבדיקות פה שוב או שניתן לשלוח מפה את זה לבדיקה חוזרת בקובץ של הוולידציה שאחרי הפארסינג */

}

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

void handle_create(const char *filename) {
    char path[500];

    if (build_file_path(filename, path, sizeof(path)) == 0) {
        printf("Error: Failed to build file path.\n");
        return;
    }

    FILE *file = fopen(path, "wx");

    if (file == NULL) {
    printf("Error: Failed to create file.\n");
    return;
    } 

    if (fclose(file) != 0) {
        printf("Error: Failed to close file.\n");
        return;
    }

    printf("File created successfully.\n");
}
void handle_write(const char *filename, const char *content) {
    char path1[1200];

    if (build_file_path(filename, path1, sizeof(path1)) == 0) {
        printf("Error: Cannot build file path.\n");
        return;
    }

    FILE *file = fopen(path1, "r+");

    if (file == NULL) {
        printf("Error: Cannot open file.\n");
        return;
    }

    int fd = _fileno(file);
    if (fd == -1){
        printf("Error: Cannot get file descriptor.\n");
        fclose(file);
        return;
    }
    if(_chsize_s(fd, 0) != 0){
        printf("Error: Cannot clear file.\n");
         fclose(file);
        return;
    }

    fseek(file, 0, SEEK_SET);

    if (fseek(file, 0, SEEK_SET) != 0) {
    printf("Error: Cannot set file position.\n");
    fclose(file);
    return;
    }
    
    size_t a = fwrite(content, 1, strlen(content), file);

    if (strlen(content) != a) {
        printf("Error: Cannot write to file.\n");
        fclose(file);
        return;
    }

    if (fclose(file) != 0) {
        printf("Error: Cannot close file.\n");
        return;
    }

    printf("File written successfully.\n");
}