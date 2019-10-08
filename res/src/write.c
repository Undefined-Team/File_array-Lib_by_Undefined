#include "ud_file.h"

int     ud_file_write_ctr(char *path, ud_arr *content, int flag)
{
    if (!path)
        return (-1);
    
    if (!flag && !access(path, F_OK))
        remove(path);
    int     fd = open(path, O_RDWR | O_CREAT | flag);
    if (fd == -1)
    {
        char resolved_path[PATH_MAX];
        if (!realpath(path, resolved_path))
            ud_ut_error("Couldn't resolve absolute path.");
        ud_ut_error("Couldn't create file %s, check that the provided path exists.", resolved_path);
    }
    char    *t_content_val = (char *)content->val;
    int     w_ret = write(fd, t_content_val, content->len);
    if (w_ret == -1)
    {
        char resolved_path[PATH_MAX];
        realpath(path, resolved_path);
        ud_ut_error("Couldn't write to file %s.", resolved_path);
    }
    return (w_ret);
}