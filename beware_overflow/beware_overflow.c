#include "beware_overflow.h"

#include <assert.h>
#include <err.h>
#include <errno.h>

void *beware_overflow(void *ptr, size_t nmemb, size_t size)
{
    char *p = ptr;
    size_t res = 0;
    int overflow = __builtin_umull_overflow(nmemb, size, &res);
    return (overflow) ? NULL : p + res;
}
