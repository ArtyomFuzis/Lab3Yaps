#ifndef CONSOLE_H
#define CONSOLE_H
#include "transform.h"

struct inp_data {
    char* source_img;
    char* transformed_img;
    enum transformation transformation;
};
enum parse_status {
    PARSE_OK=0,
    PARSE_WRONG_ARGS_LENGTH,
    PARSE_NO_ARGS,
    PARSE_BAD_TRANSFORMATION
};
enum parse_transformation_status {
    PARSE_TRANSFORMATION_OK=0,
    PARSE_TRANSFORMATION_FAIL
};
enum parse_status parse_data(int argc, char** arg,struct inp_data *data);
enum parse_transformation_status parse_transformation(char const* input, enum transformation *value);
#endif //CONSOLE_H
