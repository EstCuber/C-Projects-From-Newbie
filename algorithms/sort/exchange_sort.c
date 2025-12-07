//
// Created by ivanefremov on 02.12.2025.
//


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

void _exchange_sort(
    void* base,
    size_t count,
    size_t size,
    compare_func_t cmp
    )
{
    char *ptr = (char*) base;
    void *temp = malloc(size);
    if (!temp) return;

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i+1; j < count; ++j) {

            char *a = ptr + (i * size);
            char *b = ptr + (j * size);

            if (cmp(a, b) > 0) {
                memcpy(temp, a, size);
                memcpy(a, b, size);
                memcpy(b, temp, size);
            }
        }
    }

    free(temp);
}
