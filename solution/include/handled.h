#ifndef HANDLED_H
#define HANDLED_H
#include "args.h"
#include "file.h"
#include "image.h"

enum handled_status {
    HANDLED_OK = 0,
    HANDLED_FAIL
};

enum handled_status get_data_handled(int argc, char **argv, struct inp_data *data);

enum handled_status get_datafiles_handled(struct inp_data const *data, struct data_files *data_files);

enum handled_status from_bmp_handled(struct data_files const *files, struct image *img);

enum handled_status close_datafiles_handled(struct data_files const *files);

enum handled_status to_bmp_handled(struct data_files const *files, struct image const *img);

enum handled_status transform_handled(struct inp_data const *data, struct image *img);

enum handled_status destroy_img_handled(struct image *img);
#endif //HANDLED_H
