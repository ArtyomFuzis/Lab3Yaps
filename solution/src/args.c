#include "args.h"
#include "transform.h"
#include <string.h>


struct transformations {
    char *name;
    enum transformation transformation;
} items_list[] = {
    {"none", TRANSFORM_NONE},
    {"cw90", TRANSFORM_CW90},
    {"ccw90", TRANSFORM_CCW90},
    {"fliph", TRANSFORM_FLIPH},
    {"flipv", TRANSFORM_FLIPV}
};

enum parse_transformation_status parse_transformation(char const *input, enum transformation *value) {
    for (int i = 0; i < sizeof(items_list) / sizeof(struct transformations); i++) {
        if (strcmp(input, items_list[i].name) == 0) {
            *value = items_list[i].transformation;
            return PARSE_TRANSFORMATION_OK;
        }
    }
    return PARSE_TRANSFORMATION_FAIL;
}

enum parse_status parse_data(int argc, char **argv, struct inp_data *data) {
    if (argc == 1) return PARSE_NO_ARGS;
    if (argc != 4) return PARSE_WRONG_ARGS_LENGTH;
    enum parse_transformation_status res = parse_transformation(argv[3], &data->transformation);
    if (res != PARSE_TRANSFORMATION_OK) return PARSE_BAD_TRANSFORMATION;
    data->source_img = argv[1];
    data->transformed_img = argv[2];
    return PARSE_OK;
}
