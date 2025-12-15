#include "small_string_opt.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool is_short_string(String *str) {
  unsigned char flag_byte = str->s.len_remaining_and_flag;
  return ((flag_byte & SHORT_FLAG_MASK) != 0);
}

size_t string_len(String *s) {
  if (is_short_string(s))
    return s->s.len_remaining_and_flag & LEN_MASK;

  return s->l.len;
}

char *string_text(String *s) {
  if (is_short_string(s))
    return s->s.buf;
  return s->l.ptr;
}

void set_short_string(String *s, const char *text, size_t nbytes) {
  memcpy(s->s.buf, text, nbytes);
  s->s.buf[nbytes] = '\0';
  s->s.len_remaining_and_flag = (uint8_t)nbytes | SHORT_FLAG_MASK;
}

void set_long_string(String *s, const char *text, size_t nbytes);

void set_string(String *s, const char *text, size_t nbytes);
