#include "mymalloc.h"

__attribute__((visibility("default"))) void *malloc(size_t size)
{
    return mymalloc(size);
}

__attribute__((visibility("default"))) void free(void *ptr)
{
    myfree(ptr);
    return;
}

__attribute__((visibility("default"))) void *realloc(void *ptr, size_t size)
{
    return myrealloc(ptr, size);
}

__attribute__((visibility("default"))) void *calloc(size_t nmemb, size_t size)
{
    return mycalloc(nmemb, size);
}
