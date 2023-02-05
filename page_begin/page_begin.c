#include "page_begin.h"

#include <assert.h>
#include <err.h>
#include <errno.h>

void *page_begin(void *ptr, size_t page_size)
{
    char *p = ptr;
    return p - (((page_size - 1)) & (size_t)ptr);
}
