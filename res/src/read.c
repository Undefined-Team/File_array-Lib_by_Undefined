#include "ud_file.h"

ud_arr  *ud_file_read(char *path)
{
    int     fd = open(path, O_RDONLY);
    if (!path || access(path, R_OK) || read(fd, NULL, 0) == -1)
        return (NULL);
    
    size_t  buf_size = 4096;
    ud_arr  *content = ud_arr_tinit(ud_stra_type_char(), 1);
    ud_arr  *buf = ud_arr_tinit(ud_stra_type_char(), buf_size);
    char    *t_buf_val = (char *)buf->val;
    size_t  len = 0;

    while ((len = read(fd, t_buf_val, buf_size)) > 0)
    {
        buf->len = len;
        ud_arr *content_tmp = ud_stra_cat(content, buf);
        ud_arr_free(content);
        content = content_tmp;
    }
    --content->len;
    return (content);
}