#include "small_string_opt.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

static size_t find_capacity(size_t current_len, size_t current_cap) {
  if (current_cap == 0)
    current_cap = 16;

  while (current_len > current_cap) {
    current_cap *= 2;
  }
  return current_cap;
}

static void set_short_string(String *s, const char *text, size_t nbytes) {
  memcpy(s->s.buf, text, nbytes);
  s->s.buf[nbytes] = '\0';
  s->s.len_remaining_and_flag = (uint8_t)nbytes | SHORT_FLAG_MASK;
}

static void set_long_string(String *s, const char *text, size_t nbytes) {
  size_t capacity = find_capacity(nbytes, 0);
  char *ptr = (char *)malloc(capacity + 1);
  if (!ptr)
    exit(1);

  memcpy(ptr, text, nbytes);
  s->l.ptr = ptr;
  s->l.len = nbytes;
  s->l.cap = capacity;
}

void string_reserve(String *s, size_t new_len) {
  bool is_short = is_short_string(s);
  size_t current_cap;

  if (is_short) {
    current_cap = MAX_SHORT_LEN;
  } else {
    current_cap = s->l.cap;
  }

  if (new_len <= current_cap) {
    return;
  }

  size_t new_capacity = find_capacity(new_len, current_cap);
  char *new_ptr;

  if (is_short) {
    new_ptr = (char *)malloc(new_capacity + 1);
    if (!new_ptr)
      exit(1);
    size_t old_len = s->s.len_remaining_and_flag & LEN_MASK;
    memcpy(new_ptr, s->s.buf, old_len);
    new_ptr[old_len] = '\0';

    s->l.ptr = new_ptr;
    s->l.len = old_len;
    s->l.cap = new_capacity;

  } else {
    new_ptr = realloc(s->l.ptr, new_capacity + 1);
    if (!new_ptr)
      exit(1);
    s->l.ptr = new_ptr;
    s->l.cap = new_capacity;
  }
}

void string_append(String *s, const char *text, size_t nbytes) {
  size_t current_len = string_len(s);
  size_t new_len = current_len + nbytes;

  string_reserve(s, new_len);
  char *dest = string_text(s);

  memcpy(dest + current_len, text, nbytes);
  dest[new_len] = '\0';

  if (is_short_string(s)) {
    s->s.len_remaining_and_flag = (uint8_t)new_len | SHORT_FLAG_MASK;
  } else {
    s->l.len = new_len;
  }
}

void string_new(String *s) {
  s->s.buf[0] = '\0';
  s->s.len_remaining_and_flag = 0 | SHORT_FLAG_MASK;
}

void string_from(String *s, const char *text, size_t nbytes) {
  if (nbytes <= MAX_SHORT_LEN) {
    set_short_string(s, text, nbytes);
  } else {
    set_long_string(s, text, nbytes);
  }
}
