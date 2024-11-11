#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include "image.h"

typedef void (transform_perform)(struct pixel *, struct image const *, const int, const int);

enum transformation {
    TRANSFORM_NONE = 0,
    TRANSFORM_CW90,
    TRANSFORM_CCW90,
    TRANSFORM_FLIPH,
    TRANSFORM_FLIPV
};

enum transform_status {
    TRANSFORM_OK,
    TRANSFORM_NO_MEMORY,
    TRANSFORM_FAIL
};

enum transform_status do_transform(enum transformation transform, struct image *img);
#endif //TRANSFORMATION_H
