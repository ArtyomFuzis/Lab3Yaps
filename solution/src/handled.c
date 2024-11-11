#include "handled.h"
#include "file.h"
#include "image.h"
#include "bmp.h"
#include "transform.h"
enum handled_status get_data_handled(int argc, char **argv, struct inp_data *data) {
    switch (parse_data(argc, argv, data)) {
        case PARSE_NO_ARGS:
            printf("Found no argc. Usage: image-transform <source-image> <transformed-image> <tranformation>\n");
            break;
        case PARSE_WRONG_ARGS_LENGTH:
            printf(
                "Wrong count of arguments. Usage: image-transform <source-image> <transformed-image> <tranformation>\n");
            break;
        case PARSE_BAD_TRANSFORMATION:
            printf("Unknown transformation. Avaliable transformations: none, cw90, ccw90, fliph, flipv\n");
            break;
        case PARSE_OK:
            return HANDLED_OK;
    }
    return HANDLED_FAIL;
}
enum handled_status get_datafiles_handled(struct inp_data const * data, struct data_files *files) {
    files->source_image = NULL;
    files->transformed_image= NULL;
    if(open_file_read(data->source_img, &files->source_image) == IO_FAIL) {
        printf("Source file is not accessible or does not exists.\n");
        return HANDLED_FAIL;
    }
    if(open_file_rewrite(data->transformed_img, &files->transformed_image) == IO_FAIL) {
        printf("Unable to create output file.\n");
        return HANDLED_FAIL;
    }
    return HANDLED_OK;

}
enum handled_status from_bmp_handled(struct data_files const * files, struct image* img) {
    switch (from_bmp(files->source_image,img)) {
        case READ_INVALID_HEADER:
            printf("Invalid .bmp header in source file.");
            break;
        case READ_INVALID_BITS:
            break;
        case READ_INVALID_SIGNATURE:
            printf("File signature does not correspondes the header.");
            break;
        case READ_OK:
            return HANDLED_OK;
        case READ_NO_MEMORY:
            printf("Not enough memory to load this picture.");
            break;
    }
    return HANDLED_FAIL;
}
enum handled_status close_datafiles_handled(struct data_files const* files) {
    printf("files->source_image: %p\n",(void*)files->source_image);
    if(files->source_image != NULL) {
        if(close_file(files->source_image)==IO_FAIL)printf("IO Closing Error.");
    }
    if(files->transformed_image != NULL) {
        if(close_file(files->transformed_image)==IO_FAIL)printf("IO Closing Error.");
    }
    return HANDLED_OK;
}
enum handled_status to_bmp_handled(struct data_files const * files, struct image const* img) {
    switch (to_bmp(files->transformed_image,img)) {
        case WRITE_ERROR_NO_MEMORY:
            printf("Not enough memory to continue doing the writing operations.");
            break;
        case WRITE_OK:
            return HANDLED_OK;
        case WRITE_ERROR:
            printf("Writing error");
        break;
    }
    return HANDLED_FAIL;
}
enum handled_status transform_handled(struct inp_data const * data, struct image* img) {
    switch (do_transform(data->transformation,img)) {
        case TRANSFORM_NO_MEMORY:
            printf("Not enough memory to continue doing the transformation operations.");
            break;
        case TRANSFORM_FAIL:
            printf("Unknown transformation fail.");
            break;
        case TRANSFORM_OK:
            return HANDLED_OK;
    }
    return HANDLED_FAIL;
}
enum handled_status destroy_img_handled(struct image * img) {
    if(free_img(img) != IMG_OK)return HANDLED_FAIL;
    return HANDLED_OK;
}