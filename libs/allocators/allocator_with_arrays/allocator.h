#ifndef C_PROJECT_FROM_NEWBIE_ALLOCATOR_LIST_H
#define C_PROJECT_FROM_NEWBIE_ALLOCATOR_LIST_H

#include <stdio.h>

typedef enum {
  DBG_ALLOC_NOT_FREE = 0,
  DBG_ALLOC_FREE = 1,
  DBG_ALLOC_ALL = 2
} DebugAllocFlag;

void *malloc(size_t size);
void free(void *block);
void *calloc(size_t num, size_t nsize);
void *realloc(void *block, size_t size);
void info_alloc(DebugAllocFlag flag);
#endif
