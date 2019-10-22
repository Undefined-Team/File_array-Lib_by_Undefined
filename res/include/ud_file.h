#ifndef UD_FILE_H
# define UD_FILE_H

// Lib
#include <unistd.h> // for read and write
#include <stdio.h> // for remove
#include <fcntl.h> // for open
#include <stdlib.h> // for realpath
#include <limits.h> // for PATH_MAX
#include <ud_string_array.h>
#include <ud_list.h>

// Macro
# define ud_file_write(path, content)           ud_file_write_ctr(path, content, 0)
# define ud_file_write_append(path, content)    ud_file_write_ctr(path, content, O_APPEND)
# define BUF_SIZE                               4096

// Structures

// Prototypes
ud_arr  *ud_file_read(char *path);
int     ud_file_write_ctr(char *path, ud_arr *content, int flag);

#endif