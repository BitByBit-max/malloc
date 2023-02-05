CC = gcc
CPPFLAGS = -D_DEFAULT_SOURCE -I./src/
CFLAGS = -Wall -Wextra -Werror -std=c99 -fPIC -fno-builtin -Wvla
LDFLAGS = -shared
VPATH = src

TARGET_LIB = libmalloc.so
OBJS = mymalloc.o bucket.o

all: library

library: $(TARGET_LIB)
$(TARGET_LIB): CFLAGS += -pedantic -fvisibility=hidden
$(TARGET_LIB): LDFLAGS += -Wl,--no-undefined
$(TARGET_LIB): malloc.o $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

test: CFLAGS += -g -fsanitize=address
test: $(OBJS) tests/malloc_tests.o
	$(CC) -lcriterion $^ -o $@ -fsanitize=address

check: test

debug: CFLAGS += -g
debug: clean $(TARGET_LIB)

clean:
	$(RM) $(TARGET_LIB) $(OBJS) malloc.o test tests/malloc_tests.o

.PHONY: all $(TARGET_LIB) clean
