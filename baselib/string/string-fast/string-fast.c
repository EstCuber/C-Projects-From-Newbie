#include "string-fast.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_CAPACITY 16
// добавить версию без двойного указателя
// написать шорт стринг оптимизацию с union
static string *safe_malloc_create_string(string **new_string, size_t size) {
  *new_string = (string *)malloc(sizeof(string));
  if (*new_string == NULL) {
    perror("Error to create string!");
    return NULL;
  }

  size_t capacity = (size > 0) ? size : DEFAULT_CAPACITY;
  (*new_string)->chars = (char *)malloc(capacity + 1);
  if ((*new_string)->chars == NULL) {
    perror("Error to create string!");
    free(*new_string);
    return NULL;
  }

  (*new_string)->cap = capacity;
  (*new_string)->len = size;

  (*new_string)->chars[(*new_string)->len] = '\0';
  return *new_string;
}

static size_t find_capacity(size_t current_len, size_t current_cap) {
  if (current_cap == 0)
    current_cap = 16;

  while (current_len > current_cap) {
    current_cap *= 2;
  }
  return current_cap;
}

static void safe_realloc(string *new_string, size_t current_len) {
  size_t capacity = new_string->cap;
  if (current_len > capacity) {
    size_t new_capacity = find_capacity(current_len, capacity);
    char *new_chars = realloc(new_string->chars, new_capacity + 1);
    if (new_chars == NULL) {
      perror("Error to realloc!");
      exit(1);
    }

    new_string->chars = new_chars;
    new_string->cap = new_capacity;
  }
}
void update_len(string *str, size_t count) {
  size_t len = str->len + count;
  if (len > str->cap) {
    safe_realloc(str, len);
  }
  str->len = len;
}

static string *create_string_impl(char *symbols, size_t nbytes) {
  string *new_string;
  if ((safe_malloc_create_string(&new_string, nbytes)) == NULL) {
    return NULL;
  }
  memcpy(new_string->chars, symbols, nbytes);
  return new_string;
}

// other variation from Zhurman
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define DEFAULT_CAPACITY 16

// typedef struct {
//     char *chars;
//     size_t cap;
//     size_t len;
// } string;

// const string nostr = {0};

// static string safe_malloc_create_string(size_t len) {
//     string new_string;

//     size_t capacity = (len > 0) ? len : DEFAULT_CAPACITY;

//     new_string.chars = (char *)malloc(capacity + 1);
//     if (new_string.chars == NULL) {
//         perror("Error to create string!");
//         return nostr;
//     }

//     memset(new_string.chars, 0, capacity + 1);
//     new_string.cap = capacity;
//     new_string.len = len;

//     return new_string;
// }

// int main() {
//     string s = safe_malloc_create_string(5);

//     strcpy(s.chars, "Hello");
//     printf("%s (len=%zu, cap=%zu)\n", s.chars, s.len, s.cap);
//     free(s.chars);

//     return 0;
// }
