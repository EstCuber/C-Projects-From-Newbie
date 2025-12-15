#ifndef C_PROJECTS_FROM_NEWBIE_BASELIB_STRING_FAST
#define C_PROJECTS_FROM_NEWBIE_BASELIB_STRING_FAST

#include <stdio.h>

typedef struct string {
  char *chars;
  size_t len;
  size_t cap;
} string;

#endif
