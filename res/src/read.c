#include "ud_file.h"

ud_arr  *ud_file_read(char *path)
{
    int     fd = open(path, O_RDONLY);
    if (!path || access(path, R_OK) || read(fd, NULL, 0) == -1)
        return (NULL);
    
    size_t  buf_size = 4096;
    char    buf[buf_size];
    size_t  len = 0;
    size_t  total_len = 0;
    ud_list *buf_list = NULL;
    ud_list *curr = NULL;

    while ((len = read(fd, buf, buf_size)) > 0)
    {
        if ((!buf_list && !(buf_list = ud_list_init(buf))) || (curr && !(curr = ud_list_add_last(curr, buf))))
            return NULL;
        total_len += len;
    }

    ud_arr  *content = ud_arr_tinit(ud_stra_type_char(), total_len + 1);
    char    *t_content_val = (char *)content->val;
    ud_list *buf_list_tmp = buf_list;
    ud_list *tmp_free;

    while (buf_list_tmp)
    {
        char *list_data = (char *)buf_list_tmp->data;
        ud_mem_cpy_rd(t_content_val, list_data, buf_list_tmp->next ? 4096 : total_len % 4096);
        tmp_free = buf_list_tmp;
        buf_list_tmp = buf_list_tmp->next;
        ud_ut_free(tmp_free);
    }
    
    return content;
}