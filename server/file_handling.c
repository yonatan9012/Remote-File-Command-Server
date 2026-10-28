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

    char path[512];

    build_file_path(filename, path, sizeof(path));
}