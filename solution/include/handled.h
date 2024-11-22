#ifndef HANDLED_H
#define HANDLED_H
#include "args.h"
#include "file.h"
#include "image.h"

enum handled_status {
    HANDLED_OK = 0,
    HANDLED_FAIL
};

struct handled_res {
    enum handled_status status;
    int err_code;
};

struct handled_res get_data_handled(int argc, char **argv, struct inp_data *data);

struct handled_res get_datafiles_handled(struct inp_data const *data, struct data_files *data_files);

struct handled_res from_bmp_handled(struct data_files const *files, struct image *img);

struct handled_res close_datafiles_handled(struct data_files const *files);

struct handled_res to_bmp_handled(struct data_files const *files, struct image const *img);

struct handled_res transform_handled(struct inp_data const *data, struct image *img);

struct handled_res destroy_img_handled(struct image *img);
#endif //HANDLED_H
