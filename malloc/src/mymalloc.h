#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include "bucket.h"

size_t align(size_t size, size_t modulo);
void *mymalloc(size_t size);
void *mycalloc(size_t nmem, size_t size);
void myfree(void *ptr);
void *myrealloc(void *ptr, size_t size);

#endif /* ! MYMALLOC_H */
