#include "file.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int try_op_file(char *filename, int flags, int mode) {
  int fp;
  if ((fp = open(filename, flags, mode)) < 0) {
    perror("Error open file");
    return -1;
  }
  return fp;
}

int fatal_op_file(char *filename, int flags, int mode) {
  int fp;
  if ((fp = try_op_file(filename, flags, mode)) < 0) {
    exit(1);
  }
  return fp;
}

int try_wr_file_raw(int fd, const char *buffer, size_t nbytes) {
  if (write(fd, buffer, nbytes) != nbytes) {
    perror("Error write in file");
    return -1;
  }
  return 0;
}
int fatal_wr_file_raw(int fd, const char *buffer, size_t nbytes) {
  if (try_wr_file_raw(fd, buffer, nbytes)) {
    exit(1);
  }
  return 0;
}
