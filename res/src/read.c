#include "ud_file.h"

ud_arr  *ud_file_read(char *path)
{
    int     fd = open(path, O_RDONLY);
    if (!path || access(path, R_OK) || read(fd, NULL, 0) == -1)
        return (NULL);
    
    size_t              buf_size = 4096;
    char                buf[buf_size];
    size_t              len = 0;
    size_t              total_len = 0;

    typedef struct      uds_file_read_list {
        void            (*fp_free)(void *val);
        struct          uds_file_read_list *next;
        char            data[buf_size];
    }                   ud_file_read_list;

    ud_file_read_list   *buf_list = NULL;
    ud_file_read_list   *curr = NULL;

    len = read(fd, buf, buf_size);
    total_len += len;
    buf_list = ud_list_minit(ud_file_read_list);
    ud_mem_cpy(buf_list->data, buf, len);
    curr = buf_list;
    while ((len = read(fd, buf, buf_size)) > 0)
    {
        curr = ud_list_mpush_last(ud_file_read_list, curr);
        ud_mem_cpy(curr->data, buf, len);
        total_len += len;
    }

    ud_arr  *content = ud_arr_tinit(ud_stra_type_char(), total_len + 1);
    char    *t_content_val = (char *)content->val;
    curr = buf_list;
    while (curr)
    {
        ud_mem_cpy_rd(t_content_val, (char *)curr->data, curr->next ? buf_size : total_len % buf_size);
        curr = curr->next;
    }
    ud_list_free(buf_list);

    return content;
}