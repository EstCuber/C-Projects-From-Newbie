#ifndef C_PROJECTS_FROM_NEWBIE_EXCHANGE_SORT_H
#define C_PROJECTS_FROM_NEWBIE_EXCHANGE_SORT_H
#include <stdio.h>

typedef int (compare_func_t)(const void*, const void*);

void _exchange_sort(
    void *base, 
    size_t count, 
    size_t size, 
    compare_func_t cmp
);

#define exchange_sort(base, count, cmp) _exchange_sort(base, count, sizeof(*base), cmp)

typedef struct ArrObj {
    int *arr;
    int size;
} ArrObj;

#endif