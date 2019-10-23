#ifndef UD_FILE_ARRAY_H
# define UD_FILE_ARRAY_H

// Lib
#include <unistd.h> // for read and write
#include <stdio.h> // for remove
#include <fcntl.h> // for open
#include <stdlib.h> // for realpath
#include <limits.h> // for PATH_MAX
#include <ud_string_array.h>
#include <ud_file.h>

// Macro
# define ud_file_array_write(_path, _content)           ud_file_write_ctr(_path, (char *)_content->val, 0)
# define ud_file_array_write_append(_path, _content)    ud_file_write_ctr(_path, (char *)_content->val, O_APPEND)
# define BUF_SIZE                                       4096

// Structures

// Prototypes
ud_arr  *ud_file_array_read(char *path);
int     ud_file_array_write_ctr(char *path, ud_arr *content, int flag);
void    ud_file_array_clear(char *path);

#endif