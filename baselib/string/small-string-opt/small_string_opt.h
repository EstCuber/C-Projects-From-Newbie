#ifndef C_PROC_PROJECTS_FROM_NEWBIE_BASELIB_STRING_OPT
#define C_PROC_PROJECTS_FROM_NEWBIE_BASELIB_STRING_OPT

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define SHORT_FLAG_MASK 0x80
#define LEN_MASK 0x7F

// SSO
typedef struct {
  char *ptr;
  size_t len;
  size_t cap;
} LongString;

typedef struct {
  char buf[sizeof(LongString) - 1];
  uint8_t len_remaining_and_flag;
} ShortString;

typedef struct {
  union {
    LongString l;
    ShortString s;
  };
} String;

#endif
