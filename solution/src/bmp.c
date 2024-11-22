#include "bmp.h"
#include "image.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bmp_header_const 0x4d42
#define bmp_header_size_field 40
#define bmp_header_bit_cnt 24

uint32_t get_line_size(uint32_t biWidth) {
    return biWidth * sizeof(struct pixel) + (4 - (biWidth * sizeof(struct pixel)) % 4) % 4;
}

enum read_status from_bmp(FILE *in, struct image *img) {
    struct bmp_header header;
    size_t res = fread(&header, sizeof(header), 1, in);
    if (res < 1)return READ_IO_ERROR;
    if (ferror(in)) return READ_IO_ERROR;
    img->height = header.biHeight;
    img->width = header.biWidth;
    enum img_status status = init_img(img);
    if (status == IMG_NO_MEMORY)return READ_NO_MEMORY;
    uint32_t lineSize = get_line_size(header.biWidth);
    char *cur_line = malloc(lineSize);
    if (cur_line == NULL) {
        free_img(img);
        return READ_NO_MEMORY;
    }
    for (size_t i = 0; i < img->height; i++) {
        res = fread(cur_line, sizeof(char), lineSize, in);
        if (res < lineSize || ferror(in)) {
            free(cur_line);
            return READ_INVALID_SIGNATURE;
        }
        memcpy((char *) img->data + i * img->width * sizeof(struct pixel), cur_line, img->width * sizeof(struct pixel));
    }
    /*printf("Height: %d\n",header.biHeight);
    printf("Width: %d\n",header.biWidth);
    printf("Size: %d\n",header.biSize);
    printf("SizeImage: %d\n",header.biSizeImage);
    printf("BitCount: %d\n",header.biBitCount);
    printf("Offset: %d\n",header.bOffBits);
    printf("Compression: %d\n",header.biCompression);
    printf("biXPelsPerMeter: %d\n",header.biXPelsPerMeter);
    printf("biYPelsPerMeter: %d\n",header.biYPelsPerMeter);
    printf("biClrUsed: %d\n",header.biClrUsed);
    printf("biClrImportant: %d\n",header.biClrImportant);
    printf("bfType: %d\n",header.bfType);
    printf("bfileSize: %d\n",header.bfileSize);
    printf("bOffBits: %d\n",header.bOffBits);*/
    free(cur_line);
    return READ_OK;
}

struct bmp_header get_bmp_header(struct image const *img) {
    uint32_t lineSize = get_line_size(img->width);
    struct bmp_header header = {
        .bfType = bmp_header_const,
        .bfileSize = sizeof(struct bmp_header) + lineSize * img->height,
        .bfReserved = 0,
        .bOffBits = sizeof(struct bmp_header),
        .biSize = bmp_header_size_field,
        .biWidth = img->width,
        .biHeight = img->height,
        .biPlanes = 1,
        .biBitCount = bmp_header_bit_cnt,
        .biCompression = 0,
        .biSizeImage = lineSize * img->height,
        .biXPelsPerMeter = 0,
        .biYPelsPerMeter = 0,
        .biClrUsed = 0,
        .biClrImportant = 0,
    };
    return header;
}

enum write_status to_bmp(FILE *out, struct image const *img) {
    struct bmp_header header = get_bmp_header(img);
    size_t res = fwrite(&header, sizeof(header), 1, out);
    if (res < 1)return WRITE_ERROR;
    if (ferror(out)) return WRITE_ERROR;
    uint32_t lineSize = get_line_size(header.biWidth);
    char *cur_line = malloc(lineSize);
    if (cur_line == NULL) {
        return WRITE_ERROR_NO_MEMORY;
    }
    for (int i = 0; i < lineSize; i++)cur_line[i] = 0;
    for (size_t i = 0; i < img->height; i++) {
        memcpy(cur_line, (char *) img->data + i * img->width * sizeof(struct pixel), img->width * sizeof(struct pixel));
        res = fwrite(cur_line, sizeof(char), lineSize, out);
        if (res < lineSize || ferror(out)) {
            free(cur_line);
            return WRITE_ERROR;
        }
    }
    free(cur_line);
    return WRITE_OK;
}
