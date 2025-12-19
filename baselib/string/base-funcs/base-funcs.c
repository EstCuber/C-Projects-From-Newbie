#include "base-funcs.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int try_op_file(const char *filename, int flags, int mode) {
  int fd;
  if ((fd = open(filename, flags, mode)) < 0) {
    perror("Error open file");
    return -1;
  }
  return fd;
}

int fatal_op_file(const char *filename, int flags, int mode) {
  int fd;
  if ((fd = try_op_file(filename, flags, mode)) < 0) {
    exit(1);
  }
  return fd;
}

int try_wr_file_raw(int fd, const char *buffer, size_t nbytes) {
  ssize_t bytes_write;
  if ((bytes_write = write(fd, buffer, nbytes)) != nbytes) {
    perror("Error write in file");
    return -1;
  }
  return bytes_write;
}
int fatal_wr_file_raw(int fd, const char *buffer, size_t nbytes) {
  ssize_t bytes_write;
  if ((bytes_write = try_wr_file_raw(fd, buffer, nbytes)) != nbytes) {
    exit(1);
  }
  return bytes_write;
}

ssize_t try_read_buffer_raw(int fd, char *buffer, size_t nbytes) {
  ssize_t bytes_read = read(fd, buffer, nbytes);
  if ((bytes_read) < 0) {
    perror("Error reading file");
  }
  return bytes_read;
}

ssize_t fatal_read_buffer_raw(int fd, char *buffer, size_t nbytes) {
  ssize_t bytes_read = try_read_buffer_raw(fd, buffer, nbytes);
  if ((bytes_read) < 0) {
    exit(1);
  }
  return bytes_read;
}

ssize_t safe_write(int fd, const char *buffer, size_t nbytes) {
  size_t written = 0;
  while (written < nbytes) {
    ssize_t n = try_wr_file_raw(fd, buffer + written, nbytes - written);
    if (n < 0) {
      return -1;
    }
    written += n;
  }
  return 0;
}

ssize_t safe_read(int fd, char *buffer, size_t nbytes) {
  size_t readed = 0;
  while (readed < nbytes) {
    ssize_t n = try_read_buffer_raw(fd, buffer + readed, nbytes - readed);
    if (n < 0) {
      return n;
    }
    if (n == 0) {
      break;
    }
    readed += n;
  }
  return 0;
}
