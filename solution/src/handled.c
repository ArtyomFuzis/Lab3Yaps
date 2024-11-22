#include "bmp.h"
#include "args.h"
#include "file.h"
#include "handled.h"
#include "image.h"
#include "transform.h"
#include <errno.h>
#include <stdio.h>
struct handled_res get_data_handled(int argc, char **argv, struct inp_data *data) {
    switch (parse_data(argc, argv, data)) {
        case PARSE_NO_ARGS:
            printf("Found no argc. Usage: image-transform <source-image> <transformed-image> <tranformation>\n");
            return (struct handled_res) {HANDLED_FAIL, ENOEXEC};
        case PARSE_WRONG_ARGS_LENGTH:
            printf("Wrong count of arguments. Usage: image-transform <source-image> <transformed-image> <tranformation>\n");
            return (struct handled_res){HANDLED_FAIL, E2BIG};
        case PARSE_BAD_TRANSFORMATION:
            printf("Unknown transformation. Avaliable transformations: none, cw90, ccw90, fliph, flipv\n");
            return (struct handled_res){HANDLED_FAIL, EINVAL};
        case PARSE_OK:
            return (struct handled_res){HANDLED_OK,0};
    }
    return (struct handled_res){HANDLED_FAIL, ENOEXEC};
}

struct handled_res get_datafiles_handled(struct inp_data const *data, struct data_files *files) {
    files->source_image = NULL;
    files->transformed_image = NULL;
    if (open_file_read(data->source_img, &files->source_image) == IO_FAIL) {
        printf("Source file is not accessible or does not exists.\n");
        return (struct handled_res){HANDLED_FAIL, ENOENT};
    }
    if (open_file_rewrite(data->transformed_img, &files->transformed_image) == IO_FAIL) {
        printf("Unable to create output file.\n");
        return (struct handled_res){HANDLED_FAIL, EIO};
    }
    return (struct handled_res){HANDLED_OK,0};
}

struct handled_res from_bmp_handled(struct data_files const *files, struct image *img) {
    switch (from_bmp(files->source_image, img)) {
        case READ_INVALID_HEADER:
            printf("Invalid .bmp header in source file.");
            return (struct handled_res){HANDLED_FAIL, ENOEXEC};
        case READ_INVALID_BITS:
            return (struct handled_res){HANDLED_FAIL, ENOEXEC};
        case READ_INVALID_SIGNATURE:
            printf("File signature does not correspondes the header.");
            return (struct handled_res){HANDLED_FAIL, ENOEXEC};
        case READ_OK:
            return (struct handled_res){HANDLED_OK,0};
        case READ_NO_MEMORY:
            printf("Not enough memory to load this picture.");
            return (struct handled_res){HANDLED_FAIL, ENOMEM};
        case READ_IO_ERROR:
            printf("Unexpected I/O error occured.");
            return (struct handled_res){HANDLED_FAIL, EIO};
    }
    return (struct handled_res){HANDLED_FAIL, ENOEXEC};
}

struct handled_res close_datafiles_handled(struct data_files const *files) {
    printf("files->source_image: %p\n", (void *) files->source_image);
    if (files->source_image != NULL) {
        if (close_file(files->source_image) == IO_FAIL)printf("IO Closing Error.");
    }
    if (files->transformed_image != NULL) {
        if (close_file(files->transformed_image) == IO_FAIL)printf("IO Closing Error.");
    }
    return (struct handled_res){HANDLED_OK,0};
}

struct handled_res to_bmp_handled(struct data_files const *files, struct image const *img) {
    switch (to_bmp(files->transformed_image, img)) {
        case WRITE_ERROR_NO_MEMORY:
            printf("Not enough memory to continue doing the writing operations.");
            return (struct handled_res){HANDLED_FAIL, ENOMEM};
        case WRITE_OK:
            return (struct handled_res){HANDLED_OK,0};
        case WRITE_ERROR:
            printf("Writing error");
            return (struct handled_res){HANDLED_FAIL, EIO};
    }
    return (struct handled_res){HANDLED_FAIL, ENOEXEC};
}

struct handled_res transform_handled(struct inp_data const *data, struct image *img) {
    switch (do_transform(data->transformation, img)) {
        case TRANSFORM_NO_MEMORY:
            printf("Not enough memory to continue doing the transformation operations.");
            return (struct handled_res){HANDLED_FAIL, ENOMEM};
        case TRANSFORM_FAIL:
            printf("Unknown transformation fail.");
            return (struct handled_res){HANDLED_FAIL, ENOEXEC};
        case TRANSFORM_OK:
            return (struct handled_res){HANDLED_OK,0};
    }
    return (struct handled_res){HANDLED_FAIL, ENOEXEC};
}

struct handled_res destroy_img_handled(struct image *img) {
    if (free_img(img) != IMG_OK)return (struct handled_res){HANDLED_FAIL, ENOEXEC};
    return (struct handled_res){HANDLED_OK,0};
}
