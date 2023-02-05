#include "alignment.h"

#include <assert.h>
#include <err.h>
#include <errno.h>

size_t align(size_t size)
{
    if (0 == size % sizeof(long double))
    {
        return size;
    }
    size_t i = size - (size % sizeof(long double));
    size_t res = 0;
    return (__builtin_uaddl_overflow(i, sizeof(long double), &res)) ? 0 : res;
}
#if 0
int main(void)
{
    printf("%d\n", align(13) == 16);
    printf("%d\n", align(-1) == 0);
    printf("%d\n", align(0) == 0);
    printf("%d\n", align(sizeof(long double)) == 16);
    printf("%lu\n", sizeof(long double));
    return 0;
}
#endif /* main */
