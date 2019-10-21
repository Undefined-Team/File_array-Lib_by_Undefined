#include "ud_file.h"

typedef struct  uds_file_read_list {
    char *data;
    struct uds_file_read_list *next;
}               ud_file_read_list;

ud_arr  *ud_file_read(char *path)
{
    int     fd = open(path, O_RDONLY);
    if (!path || access(path, R_OK) || read(fd, NULL, 0) == -1)
        return (NULL);
    
    size_t  buf_size = 4096;
    char    buf[buf_size];
    size_t  len = 0;
    size_t  total_len = 0;
    ud_file_read_list *buf_list = NULL;
    ud_file_read_list *curr = NULL;

    while ((len = read(fd, buf, buf_size)) > 0)
    {
        if ((!buf_list && !(buf_list = ud_list_init(ud_file_read_list, data = buf))) || (curr && !(curr = ud_list_push_last(ud_file_read_list, curr, data = buf))))
            return NULL;
        total_len += len;
    }

    ud_arr  *content = ud_arr_tinit(ud_stra_type_char(), total_len + 1);
    char    *t_content_val = (char *)content->val;
    ud_file_read_list *buf_list_tmp = buf_list;
    ud_file_read_list *tmp_free;

    while (buf_list_tmp)
    {
        ud_mem_cpy_rd(t_content_val, (char *)buf_list_tmp->data, buf_list_tmp->next ? 4096 : total_len % 4096);
        tmp_free = buf_list_tmp;
        buf_list_tmp = buf_list_tmp->next;
        ud_ut_free(tmp_free);
    }

    return content;
}