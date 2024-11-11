#include <stdio.h>
#include "err.h"
#include "args.h"
#include "handled.h"
#include "file.h"
#include "image.h"

int main(int argc, char **argv) {
    struct inp_data data;
    if (get_data_handled(argc, argv, &data) == HANDLED_FAIL) {
        return ERR_PARSE_INPUT;
    }
    struct data_files files;
    if (get_datafiles_handled(&data, &files) == HANDLED_FAIL) {
        close_datafiles_handled(&files);
        return ERR_FILE_IO;
    };
    struct image img;
    if (from_bmp_handled(&files, &img)) {
        close_datafiles_handled(&files);
        destroy_img_handled(&img);
        return ERR_FILE_FORMAT;
    };
    if (transform_handled(&data,&img)) {
        close_datafiles_handled(&files);
        destroy_img_handled(&img);
        return ERR_TRANSFORM;
    };
    if (to_bmp_handled(&files, &img)) {
        close_datafiles_handled(&files);
        destroy_img_handled(&img);
        return ERR_WRITE;
    }
    close_datafiles_handled(&files);
    destroy_img_handled(&img);
    return ERR_OK;
}
