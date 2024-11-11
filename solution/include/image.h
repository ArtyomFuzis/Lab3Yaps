#ifndef IMAGE_H
#define IMAGE_H
#include  <stdint.h>

struct pixel {
    uint8_t b, g, r;
};

enum img_status {
    IMG_OK = 0,
    IMG_NO_MEMORY
};

struct image {
    uint64_t width, height;
    struct pixel *data;
};

enum img_status init_img(struct image *img);

enum img_status free_img(struct image *img);
#endif //IMAGE_H
