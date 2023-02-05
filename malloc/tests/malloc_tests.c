#include <criterion/criterion.h>

#include "mymalloc.h"

Test(malloc, basic_char)
{
    char *p = mymalloc(sizeof(char));
    cr_assert_not_null(p);
    *p = 'c';
    char actual = *p;
    char expected = 'c';
    cr_assert_eq(actual, expected, "Expected %c. Got %c.", expected, actual);
}

Test(malloc, two_char)
{
    char *p = mymalloc(sizeof(char));
    cr_assert_not_null(p);
    *p = 'c';
    char actual = *p;
    char expected = 'c';
    cr_assert_eq(actual, expected, "Expected %c. Got %c.", expected, actual);
    char *p1 = mymalloc(sizeof(char));
    cr_assert_not_null(p1);
    *p1 = 'a';
    char actual1 = *p1;
    char expected1 = 'a';
    cr_assert_eq(actual1, expected1, "Expected %c. Got %c.", expected1,
                 actual1);
}

Test(malloc, basic_int)
{
    int *p = mymalloc(sizeof(int));
    cr_assert_not_null(p);
    *p = 3;
    int actual = *p;
    int expected = 3;
    cr_assert_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(malloc, two_strings)
{
    char *p = mymalloc(sizeof(char) * (5 + 1));
    cr_assert_not_null(p);
    p[0] = 'e';
    p[1] = 'l';
    p[2] = 'i';
    p[3] = 's';
    p[4] = 'e';
    p[5] = '\0';
    char *actual = "elise";
    char *expected = p;
    cr_assert_str_eq(actual, expected, "Expected %s. Got %s.", expected,
                     actual);
    char *p1 = mymalloc(sizeof(char) * (7 + 1));
    cr_assert_not_null(p1);
    p1[0] = 'b';
    p1[1] = 'a';
    p1[2] = 't';
    p1[3] = 'u';
    p1[4] = 'r';
    p1[5] = 'o';
    p1[6] = 'n';
    p1[7] = '\0';
    char *actual1 = "baturon";
    char *expected1 = p1;
    cr_assert_str_eq(actual1, expected1, "Expected %s. Got %s.", expected1,
                     actual1);
}

Test(malloc, multi_size)
{
    char *p1 = mymalloc(sizeof(char));
    cr_assert_not_null(p1);
    *p1 = 'c';
    char actual1 = *p1;
    char expected1 = 'c';
    cr_assert_eq(actual1, expected1, "Expected %d. Got %d.", expected1,
                 actual1);
    int *p2 = mymalloc(sizeof(int) * 3);
    cr_assert_not_null(p2);
    p2[0] = 42;
    p2[1] = 69;
    p2[2] = 0;
    int actual21 = p2[0];
    int actual22 = p2[1];
    int actual23 = p2[2];
    int expected21 = 42;
    int expected22 = 69;
    int expected23 = 0;
    cr_assert_eq(actual21, expected21, "Expected %d. Got %d.", expected21,
                 actual21);
    cr_assert_eq(actual22, expected22, "Expected %d. Got %d.", expected22,
                 actual22);
    cr_assert_eq(actual23, expected23, "Expected %d. Got %d.", expected23,
                 actual23);
    void *p3 = mymalloc(sizeof(void *) * (5 + 1));
    cr_assert_not_null(p3);
    p3 = "hello";
    char *actual3 = p3;
    char *expected3 = "hello";
    cr_assert_eq(actual3, expected3, "Expected %d. Got %d.", expected3,
                 actual3);
}

Test(calloc, basic_int)
{
    int *p = mycalloc(sizeof(int), 1);
    cr_assert_not_null(p);
    int actual = *p;
    int expected = 0;
    cr_assert_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(calloc, basic_char)
{
    char *p = mycalloc(sizeof(char), 1);
    cr_assert_not_null(p);
    char actual = *p;
    char expected = '\0';
    cr_assert_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(calloc, basic_string)
{
    char *p = mycalloc(sizeof(char), 6);
    cr_assert_not_null(p);
    char actual0 = p[0];
    char actual1 = p[1];
    char actual2 = p[2];
    char actual3 = p[3];
    char actual4 = p[4];
    char actual5 = p[5];
    char expected = '\0';
    cr_assert_eq(actual0, expected, "Expected %d. Got %d.", expected, actual0);
    cr_assert_eq(actual1, expected, "Expected %d. Got %d.", expected, actual1);
    cr_assert_eq(actual2, expected, "Expected %d. Got %d.", expected, actual2);
    cr_assert_eq(actual3, expected, "Expected %d. Got %d.", expected, actual3);
    cr_assert_eq(actual4, expected, "Expected %d. Got %d.", expected, actual4);
    cr_assert_eq(actual5, expected, "Expected %d. Got %d.", expected, actual5);
}

Test(calloc, bucket_test)
{
    struct bucket *b = mycalloc(sizeof(struct bucket), 1);
    cr_assert_not_null(b);
    cr_assert_null(b->free);
    cr_assert_null(b->next);
    size_t actual = b->capacity;
    size_t expected = 0;
    cr_assert_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
    size_t actual1 = b->bucket_size;
    size_t expected1 = 0;
    cr_assert_eq(actual1, expected1, "Expected %d. Got %d.", expected1,
                 actual1);
}

Test(free, basic_int)
{
    int *i = mycalloc(sizeof(int), 1);
    int *p = mycalloc(sizeof(int), 1);
    myfree(p);
    int *p1 = mycalloc(sizeof(int), 1);
    cr_assert_eq(p, p1, "Expected %p. Got %p.", p, p1);
    myfree(i);
    myfree(p1);
}

Test(free, basic_char)
{
    char *i = mycalloc(sizeof(char), 1);
    char *p = mycalloc(sizeof(char), 1);
    myfree(p);
    char *p1 = mycalloc(sizeof(char), 1);
    cr_assert_eq(p, p1, "Expected %p. Got %p.", p, p1);
    myfree(i);
    myfree(p1);
}

Test(free, basic_string)
{
    char *i = mycalloc(sizeof(char), 6);
    char *p = mycalloc(sizeof(char), 6);
    myfree(p);
    char *p1 = mycalloc(sizeof(char), 6);
    cr_assert_eq(p, p1, "Expected %p. Got %p.", p, p1);
    myfree(i);
    myfree(p1);
}

Test(free, bucket_test)
{
    struct bucket *i = mycalloc(sizeof(struct bucket), 1);
    struct bucket *b = mycalloc(sizeof(struct bucket), 1);
    myfree(b);
    struct bucket *p1 = mycalloc(sizeof(struct bucket), 1);
    cr_assert_eq(b, p1, "Expected %p. Got %p.", b, p1);
    myfree(i);
    myfree(p1);
}
#if 0
Test(free, multi_size)
{
    char *p1 = mymalloc(sizeof(char));
    cr_assert_not_null(p1);
    *p1 = 'c';
    char actual1 = *p1;
    char expected1 = 'c';
    cr_assert_eq(actual1, expected1, "Expected %d. Got %d.", expected1, actual1);
    int *p2 = myrealloc(p1, sizeof(int) * 3);
    cr_assert_not_null(p2);
    p2[0] = 42;
    p2[1] = 69;
    p2[2] = 0;
    int actual21 = p2[0];
    int actual22 = p2[1];
    int actual23 = p2[2];
    int expected21 = 42;
    int expected22 = 69;
    int expected23 = 0;
    myfree(p2);
    int *p3 = mymalloc(p1, sizeof(int) * 3);
    cr_assert_eq(actual21, expected21, "Expected %d. Got %d.", expected21, actual21);
    cr_assert_eq(actual22, expected22, "Expected %d. Got %d.", expected22, actual22);
    cr_assert_eq(actual23, expected23, "Expected %d. Got %d.", expected23, actual23);
    void *p3 = myrealloc(p2, sizeof(void *) * (5 + 1));
    cr_assert_not_null(p3);
    p3 = "hello";
    char *actual3 = p3;
    char *expected3 = "hello";
    cr_assert_eq(actual3, expected3, "Expected %d. Got %d.", expected3, actual3);
}
#endif /* not finished */
