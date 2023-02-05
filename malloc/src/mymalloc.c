#include "mymalloc.h"

static struct bucket *mem = NULL;

static size_t len(struct free_list *f)
{
    size_t count = 0;
    struct free_list *p = f;
    while (p)
    {
        count++;
        p = p->next;
    }
    return count;
}

static size_t findpow(size_t size)
{
    size_t pow = 8;
    while (size > pow)
    {
        pow *= 2;
    }
    return pow;
}

void *mymalloc(size_t size)
{
    size_t alsize = align(size, sizeof(long double));
    alsize = findpow(alsize);
    if (!alsize)
    {
        // printf("alsize fucked\n");
        //  error case
        return NULL;
    }
    if (!mem)
    {
        struct bucket *b = bucket_create(alsize);
        if (!b->free)
        {
            // printf("create fucked on no mem case\n");
        }
        void *res = bucket_allocate(b);
        mem = b;
        if (!res)
        {
            // printf("res null on no mem case\n");
        }
        return res;
    }
    struct bucket *b = mem;
    while (b)
    {
        if (b->bucket_size == alsize)
        {
            if (!b->free)
            {
                break;
            }
            void *res = bucket_allocate(b);
            if (!res)
            {
                // printf("res null on no mem case\n");
            }
            return res;
        }
        b = b->next;
    }
    struct bucket *tmp = mem;
    mem = bucket_create(alsize);
    mem->next = tmp;
    if (!mem->free)
    {
        // printf("create fucked on mem no size case\n");
    }
    void *res = bucket_allocate(mem);
    if (!res)
    {
        // printf("res null on no mem case\n");
    }
    return res;
}

void *mycalloc(size_t nmemb, size_t size)
{
    size_t res = 0;
    int overflow = __builtin_umull_overflow(nmemb, size, &res);
    if (overflow)
    {
        // err case
        return NULL;
    }
    void *p = mymalloc(res);
    char *ptr = p;
    if (!ptr)
    {
        // err case
        return NULL;
    }
    for (size_t i = 0 /*sizeof(struct bucket)*/; i < res; i++)
    {
        ptr[i] = 0;
    }
    return ptr;
}

static void *page_begin(void *ptr, size_t page_size)
{
    char *p = ptr;
    return p - (((page_size - 1)) & (size_t)ptr);
}

static void rem(struct bucket *b)
{
    struct bucket *tmp = mem;
    struct bucket *prev = NULL;
    while (tmp && b != tmp)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (!tmp)
    {
        // error case
        return;
    }
    if (!prev)
    {
        mem = mem->next;
        return;
    }
    prev->next = tmp->next;
    bucket_destroy(b); // should be the same as tmp
}

void myfree(void *ptr)
{
    struct bucket *b = page_begin(ptr, sysconf(_SC_PAGESIZE));
    if (!b)
    {
        // printf("free called with null pointer\n");
        return;
    }
    struct free_list *tmp = b->free;
    b->free = ptr;
    struct free_list *fptr = ptr;
    fptr->next = tmp;
    if (len(fptr) == b->capacity)
    {
        rem(b);
    }
}

void *myrealloc(void *ptr, size_t size)
{
    if (size == 0)
    {
        myfree(ptr);
        return NULL;
    }
    if (!ptr)
    {
        return mymalloc(size);
    }
    struct bucket *b = page_begin(ptr, sysconf(_SC_PAGESIZE));
    void *dst = mymalloc(size);
    if (size > b->bucket_size)
    {
        memcpy(dst, ptr, b->bucket_size);
    }
    else
    {
        memcpy(dst, ptr, size);
    }
    if (!dst)
    {
        return ptr;
    }
    myfree(ptr);
    return dst;
}
