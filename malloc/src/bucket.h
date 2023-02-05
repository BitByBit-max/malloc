#ifndef BUCKET_H
#define BUCKET_H

#include <stddef.h>

struct bucket
{
    size_t bucket_size;
    size_t capacity;
    struct bucket *next;
    void *free; // address of the first free bucket of the free list
};

struct free_list
{
    struct free_list *next; // next free bucket
};

struct bucket *bucket_create(size_t bucket_size);
void bucket_destroy(struct bucket *r);
void *bucket_allocate(struct bucket *r);
void bucket_free(struct bucket *r, void *bucket);

#endif /* !BUCKET_H */
