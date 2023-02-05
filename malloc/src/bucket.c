#include "bucket.h"

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

size_t align(size_t size, size_t modulo)
{
    if (0 == size % modulo)
    {
        return size;
    }
    size_t i = size - (size % modulo);
    size_t res = 0;
    return (__builtin_uaddl_overflow(i, modulo, &res)) ? 0 : res;
}

struct bucket *bucket_create(size_t bucket_size)
{
    if (bucket_size == 0)
    {
        // printf("arguments fucked\n");
        return NULL;
    }
    size_t size =
        align(sizeof(struct bucket) + bucket_size, sysconf(_SC_PAGESIZE));
    struct bucket *bucket = mmap(NULL, size, PROT_READ | PROT_WRITE,
                                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (!bucket)
    {
        // printf("mmap fucked\n");
        return NULL;
    }
    bucket->bucket_size = bucket_size;
    size_t metaa = size - sizeof(struct bucket);
    bucket->capacity = (metaa) / bucket_size;
    bucket->next = NULL;
    bucket->free = bucket + 1;
    char *c = bucket->free;
    struct free_list *tmp = bucket->free;
    for (size_t i = 1; i < bucket->capacity; i++)
    {
        void *j = c + bucket_size * i;
        tmp->next = j;
        tmp = tmp->next;
    }
    tmp->next = NULL;
    return bucket;
}

void bucket_destroy(struct bucket *r)
{
    if (!r)
    {
        return;
    }
    munmap(r, r->bucket_size * r->capacity);
}

void *bucket_allocate(struct bucket *r)
{
    if (!r || !r->free)
    {
        if (!r)
        {
            // printf("allocate fucked: called with null bucket\n");
            return NULL;
        }
        // printf("allocate fucked: bucket with null free list\n");
        return NULL;
    }
    void *tmp = r->free;
    struct free_list *f = r->free;
    r->free = f->next;
    return tmp;
}

void bucket_free(struct bucket *r, void *bucket)
{
    if (!r || !bucket)
    {
        return;
    }
    struct free_list *new = bucket;
    new->next = r->free;
    r->free = new;
}

#if 0
int main(void)
{
    struct bucket *r = bucket_create(16, 64);
    printf("%p\n", r->free);
    char *bucket = bucket_allocate(r);
    printf("%p\n", r->free);
    *bucket = 'c';
    bucket_free(r, bucket);
    printf("%p\n", r->free);
    bucket_destroy(r);
    return 0;
}
#endif /* MAIN */
