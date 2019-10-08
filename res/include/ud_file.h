#ifndef UD_FILE_H
# define UD_FILE_H

// Lib
#include <unistd.h>
#include <ud_array.h>
#include <ud_string.h>

// Macro

// Structures

// Prototypes
ud_arr  *ud_file_read(char *path);
int     ud_file_write(char *path);

#endif