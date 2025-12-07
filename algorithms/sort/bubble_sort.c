//
// Created by ivanefremov on 03.12.2025.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

void _bubble_sort(
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
        for (size_t j = 0; j < count - i - 1; ++j) {
            char *a = ptr + (j * size);
            char *b = ptr + ((j+1) * size);

            if (cmp(a, b) > 0) {
                memcpy(temp, a, size);
                memcpy(a, b, size);
                memcpy(b, temp, size);
            }
        }
    }

    free(temp);
}
