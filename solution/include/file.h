#ifndef FILE_H
#define FILE_H
#include <stdio.h>
struct data_files {
    FILE* source_image;
    FILE* transformed_image;
};
enum io_status {
    IO_OK=0,
    IO_FAIL
};
enum io_status open_file_read(char const* filename, FILE** file);
enum io_status open_file_rewrite(char const* filename, FILE** file);
enum io_status close_file(FILE* file);
#endif //FILE_H
