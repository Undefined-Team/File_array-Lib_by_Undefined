#include "ud_file_array.h"

void    ud_filea_clear(char *path)
{
    ud_arr *eraser = ud_stra_new("");
    ud_file_write(path, eraser);
    ud_ut_free(eraser);
}