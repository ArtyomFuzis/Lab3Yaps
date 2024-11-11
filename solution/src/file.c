#include "file.h"
#include <stddef.h>
#include <stdio.h>

enum io_status open_file_read(char const *filename, FILE **file) {
    *file = fopen(filename, "rb");
    if (*file == NULL)return IO_FAIL;
    return IO_OK;
}

enum io_status open_file_rewrite(char const *filename, FILE **file) {
    *file = fopen(filename, "wb");
    if (*file == NULL)return IO_FAIL;
    return IO_OK;
}

enum io_status close_file(FILE *file) {
    if (fclose(file) == EOF)return IO_FAIL;
    return IO_OK;
}
