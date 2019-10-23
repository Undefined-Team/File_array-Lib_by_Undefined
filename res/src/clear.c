#include "ud_file.h"

void    ud_file_clear(char *path)
{
    ud_arr *eraser = ud_stra_new("");
    ud_file_write(path, eraser);
    ud_arr_free(eraser);
}