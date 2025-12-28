#include "pthread.h"
#include <bits/pthreadtypes.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
typedef char ALIGN[32];

union header {
  struct {
    size_t size;
    unsigned is_free;
    union header *next;
    union header *prev;
  } s;
  ALIGN stub;
};
typedef union header header_t;

pthread_mutex_t global_malloc_lock;
header_t *head = NULL;
header_t *tail = NULL;

header_t *split_block(header_t *header, size_t size) {
  header_t *res_header;
  if ((size + sizeof(header_t)) < header->s.size) {
    size_t remaining_size = header->s.size - size - sizeof(header_t);
    res_header =
        (header_t *)((char *)header + sizeof(header_t) + remaining_size);
    header->s.size = remaining_size;
    res_header->s.size = size;
    res_header->s.is_free = 0;
    header->s.is_free = 1;
    res_header->s.prev = header;
    if (header->s.next != NULL) {
      header->s.next->s.prev = res_header;
      res_header->s.next = header->s.next;
      header->s.next = res_header;
    } else {
      header->s.next = res_header;
      tail = res_header;
      res_header->s.next = NULL;
    }
    return res_header;
  }
  return header;
}

header_t *get_free_block(size_t size) {
  header_t *current_header = head;
  while (current_header) {

    if ((current_header->s.is_free == 1) && (current_header->s.size >= size)) {
      return current_header;
    } else {
      current_header = current_header->s.next;
    }
  }
  return NULL;
}

void *malloc(size_t size) {
  size_t total_size;
  void *block;
  header_t *header;
  if (!size) {
    return NULL;
  }
  pthread_mutex_lock(&global_malloc_lock);
  header = get_free_block(size);
  if (header) {
    header->s.is_free = 0;
    header = split_block(header, size);
    pthread_mutex_unlock(&global_malloc_lock);
    return (void *)(header + 1);
  }
  total_size = sizeof(header_t) + size;
  block = sbrk(total_size);
  if (block == (void *)-1) {
    pthread_mutex_unlock(&global_malloc_lock);
    return NULL;
  }
  header = block;
  header->s.size = size;
  header->s.is_free = 0;
  header->s.next = NULL;
  if (!head) {
    head = header;
    header->s.prev = NULL;
  }
  if (tail) {
    tail->s.next = header;
    header->s.prev = tail;
  }
  tail = header;
  pthread_mutex_unlock(&global_malloc_lock);
  return (void *)(header + 1);
}

void free(void *block) {
  header_t *header, *tmp;
  void *programbreak;

  if (!block) {
    return;
  }
  pthread_mutex_lock(&global_malloc_lock);
  header = (header_t *)block - 1;

  programbreak = sbrk(0);

  if ((uint8_t *)block + header->s.size == programbreak) {
    if (head == tail) {
      head = tail = NULL;
    } else {
      tail = tail->s.prev;
      tail->s.next = NULL;
    }
    sbrk(0 - sizeof(header_t) - header->s.size);
    pthread_mutex_unlock(&global_malloc_lock);
    return;
  }
  header->s.is_free = 1;

  if (header->s.next != NULL) {
    tmp = header->s.next;
    if (tmp->s.is_free == 1) {
      header->s.size += tmp->s.size + sizeof(header_t);
      if (tmp == tail) {
        header->s.next = NULL;
        tail = header;

      } else if (tmp->s.next != NULL) {
        header->s.next = tmp->s.next;
        tmp->s.next->s.prev = header;
      }
    }
  }

  if (header->s.prev != NULL) {
    tmp = header->s.prev;
    if (tmp->s.is_free == 1) {
      tmp->s.size += header->s.size + sizeof(header_t);
      if (header->s.next != NULL) {
        tmp->s.next = header->s.next;
        header->s.next->s.prev = tmp;
      } else if (header->s.next == NULL) {
        tmp->s.next = NULL;
        tail = tmp;
      }
      header = tmp;
    }
  }
  pthread_mutex_unlock(&global_malloc_lock);
}

void *calloc(size_t num, size_t nsize) {
  size_t size;
  void *block;

  if (!num || !nsize) {
    return NULL;
  }
  size = num * nsize;
  // Проверка на переполненность. Не знаю когда она должна сработать... туплю
  if (nsize != size / num)
    return NULL;
  block = malloc(size);
  if (!block)
    return NULL;
  memset(block, 0, size);
  return block;
}

void *realloc(void *block, size_t size) {
  header_t *header;
  void *ret;
  if (!block || !size) {
    return malloc(size);
  }

  header = (header_t *)block - 1;
  if (header->s.size >= size) {
    return block;
  }
  ret = malloc(size);
  if (ret) {
    size_t copy_size = header->s.size;
    // так ведь?
    if (size > copy_size)
      copy_size = size;
    memcpy(ret, block, header->s.size);
    free(block);
  }
  return ret;
}
