#include "ud_file.h"

ud_arr  *ud_file_read(char *path)
{
    int     fd = open(path, O_RDONLY);
    if (!path || access(path, R_OK) || read(fd, NULL, 0) == -1)
        return (NULL);
    
    size_t  buf_size = 4096;
    ud_arr  *buf = ud_arr_tinit(ud_stra_type_char(), buf_size);
    char    *t_buf_val = (char *)buf->val;
    size_t  len = 0;
    size_t  total_len = 0;
    ud_list *buf_list = NULL;

    while ((len = read(fd, t_buf_val, buf_size)) > 0)
    {
        buf->len = len;
        buf_list = ud_list_init_or_push(buf_list, buf);
        total_len += len;
    }
    ud_arr *content = ud_arr_tinit(ud_stra_type_char(), total_len + 1);
    char *t_content_val = (char *)content->val;
    ud_list *buf_list_tmp = buf_list;
    while (buf_list_tmp)
    {
        ud_arr *list_data = (ud_arr *)buf_list_tmp->data;
        ud_mem_cpy_rd(t_content_val, list_data->val, list_data->len);
        buf_list_tmp = buf_list_tmp->next;
    }
    ud_list_free(buf_list);
    return (content);
}