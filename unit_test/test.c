#include <ud_file.h>
#include <ud_array.h>
#include <assert.h>

int byte_cmp(void *tens, void *arr, size_t len)
{
    char *a_tens = (char *)tens;
    char *a_arr = (char *)arr;
    for (ud_ut_count i = 0; i < len; i++)
    {
        if (a_tens[i] != a_arr[i])
            return (0);
    }
    return (1);
}

int main(void)
{
    ud_arr *ret = ud_file_read("./a26");
    ud_arr *wri = ud_str_fill('a', 26);
    
    ud_ut_time("%s", "Starting tests...");
    // Basic tests
    assert(ud_file_read("./fewfefef") == NULL);
    assert(ud_file_read("./dewdew/dewdew") == NULL);
    assert(byte_cmp(ret->val, wri->val, 26));
    assert(ud_file_write("./test", wri) == 26);
    ud_ut_time("%s", "All tests passed.");
}