#include "ud_file_array.h"

void    ud_filea_clear(char *path)
{
    char eraser[] = "";
    ud_file_write(path, eraser);
}