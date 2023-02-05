#include "allocator.h"

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

struct blk_allocator *blka_new(void)
{
    struct blk_allocator *blka = calloc(1, sizeof(struct blk_allocator));
    return blka;
}

struct blk_meta *blka_alloc(struct blk_allocator *blka, size_t size)
{
    size_t sizep = sysconf(_SC_PAGESIZE);
    size += sizeof(struct blk_meta);
    size_t mod = (size % sizep);
    size_t len = size;
    if (mod)
    {
        len = size - mod + sizep;
    }
    struct blk_meta *meta = mmap(NULL, len, PROT_READ | PROT_WRITE,
                                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (meta == MAP_FAILED)
    {
        return NULL;
    }
    meta->size = len - sizeof(struct blk_meta);
    struct blk_meta *tmp = blka->meta;
    blka->meta = meta;
    blka->meta->next = tmp;
    return meta;
}

void blka_free(struct blk_meta *blk)
{
    munmap(blk, blk->size + sizeof(struct blk_meta));
}

void blka_pop(struct blk_allocator *blka)
{
    if (!blka->meta)
    {
        return;
    }
    struct blk_meta *tmp = blka->meta->next;
    blka_free(blka->meta);
    blka->meta = tmp;
}

void blka_delete(struct blk_allocator *blka)
{
    struct blk_meta *m = blka->meta;
    while (m)
    {
        struct blk_meta *tmp = m;
        m = m->next;
        blka_free(tmp);
    }
    free(blka);
}
