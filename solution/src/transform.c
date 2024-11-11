#include <stdlib.h>
#include "transform.h"
#include "image.h"
void transform_ccw90(struct pixel* pixels,struct image const* img,const int i, const int j) {
    *(pixels+img->height*j+(img->height-i-1))= *(img->data+img->width*i+j);
}
void transform_cw90(struct pixel* pixels,struct image const* img,const int i, const int j) {
    *(pixels+img->height*(img->width-j-1)+i)= *(img->data+img->width*i+j);
}
void transform_filph(struct pixel* pixels,struct image const* img,const int i, const int j) {
    *(pixels+img->width*i+(img->width-j-1))= *(img->data+img->width*i+j);
}
void transform_filpv(struct pixel* pixels,struct image const* img,const int i, const int j) {
    *(pixels+img->width*(img->height-i-1)+j)= *(img->data+img->width*i+j);
}
enum transform_status perform_transform(transform_perform perform, struct image* img,int flip) {
    struct pixel* pixels = malloc(img->width*img->height*sizeof(struct pixel));
    if(pixels == NULL)return TRANSFORM_NO_MEMORY;
    for(int i = 0 ; i < img->height; i++) {
        for(int j = 0 ; j < img->width; j++) {
            perform(pixels,img,i,j);
        }
    }
    if(flip) {
        img->height ^= img->width;
        img->width ^= img->height;
        img->height ^= img->width;
    }
    free_img(img);
    img->data = pixels;
    return TRANSFORM_OK;
}
enum transform_status do_transform(enum transformation transform, struct image* img) {
    switch (transform) {
        case TRANSFORM_NONE:
            return TRANSFORM_OK;
        case TRANSFORM_CW90:
            return perform_transform(transform_cw90,img,1);
        case TRANSFORM_CCW90:
            return perform_transform(transform_ccw90,img,1);
        case TRANSFORM_FLIPH:
            return perform_transform(transform_filph,img,0);
        case TRANSFORM_FLIPV:
            return perform_transform(transform_filpv,img,0);
    }
    return TRANSFORM_FAIL;
}