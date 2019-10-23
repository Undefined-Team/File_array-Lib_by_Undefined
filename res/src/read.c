#include "ud_file_array.h"

ud_arr  *ud_filea_read(char *path)
{
    size_t len = 0;
    char *content = ud_file_read_ctr(path, &len);
    return ud_arr_tnew(ud_arr_type_char(), len, content);
}