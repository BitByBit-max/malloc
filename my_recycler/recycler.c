#include "recycler.h"

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct recycler *recycler_create(size_t block_size, size_t total_size)
{
    if (block_size % sizeof(size_t) != 0 || block_size == 0 || total_size == 0
        || total_size % block_size != 0)
    {
        return NULL;
    }
    struct recycler *recycler = malloc(sizeof(struct recycler));
    if (!recycler)
    {
        return NULL;
    }
    recycler->block_size = block_size;
    recycler->capacity = total_size / block_size;
    recycler->chunk = malloc(total_size);
    recycler->free = recycler->chunk;
    char *c = recycler->chunk;
    struct free_list *tmp = recycler->free;
    for (size_t i = 1; i < recycler->capacity; i++)
    {
        void *j = c + block_size * i;
        tmp->next = j;
        tmp = tmp->next;
    }
    tmp->next = NULL;
    return recycler;
}

void recycler_destroy(struct recycler *r)
{
    if (!r)
    {
        return;
    }
    free(r->chunk);
    free(r);
}

void *recycler_allocate(struct recycler *r)
{
    if (!r || !r->free)
    {
        return NULL;
    }
    struct free_list *tmp = r->free;
    struct free_list *f = r->free;
    r->free = f->next;
    return tmp;
}

void recycler_free(struct recycler *r, void *block)
{
    if (!r || !block)
    {
        return;
    }
    struct free_list *new = block;
    new->next = r->free;
    r->free = new;
}

#if 0
int main(void)
{
    struct recycler *r = recycler_create(16, 64);
    printf("%p\n", r->free);
    char *block = recycler_allocate(r);
    printf("%p\n", r->free);
    *block = 'c';
    recycler_free(r, block);
    printf("%p\n", r->free);
    recycler_destroy(r);
    return 0;
}
#endif /* MAIN */
