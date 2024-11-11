#ifndef ERR_H
#define ERR_H

enum err_code {
    ERR_OK = 0,
    ERR_PARSE_INPUT,
    ERR_FILE_IO = 2,
    ERR_FILE_FORMAT = 12,
    ERR_WRITE,
    ERR_TRANSFORM
};
#endif //ERR_H
