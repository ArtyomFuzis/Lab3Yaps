#include <stdlib.h>
#include "image.h"
enum img_status init_img(struct image* img)
{
    img->data = malloc(img->width*img->height*sizeof(struct pixel));
    if(img->data == NULL)return IMG_NO_MEMORY;
    return IMG_OK;
}
enum img_status free_img(struct image* img)
{
    free(img->data);
    return IMG_OK;
}