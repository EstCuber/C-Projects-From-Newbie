#ifndef C_PROJECTS_FROM_NEWBIE_BASELIB_STRING_LAZY
#define C_PROJECTS_FROM_NEWBIE_BASELIB_STRING_LAZY

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define try_wr_file_str(fd, buffer) try_wr_file_raw(fd, buffer, strlen(buffer))
#define fatal_wr_file_str(fd, buffer)                                          \
  fatal_wr_file_raw(fd, buffer, strlen(buffer))

#define try_create_file(filename, flags)                                       \
  try_op_file((filename), (flags) | O_CREAT, 0644)
#define try_read_file(filename, flags) try_op_file((filename), (flags), 0)
#define fatal_create_file(filename, flags)                                     \
  fatal_op_file((filename), (flags) | O_CREAT, 0644)
#define fatal_read_file(filename, flags) fatal_op_file((filename), (flags), 0)

// use only for arrays - example: char bytes[1024];
// for other - use raw version
#define try_read_buffer_array(fd, buffer)                                      \
  try_read_buffer_raw(fd, buffer, sizeof(buffer))
#define fatal_read_buffer_array(fd, buffer)                                    \
  fatal_read_buffer_raw(fd, buffer, sizeof(buffer))

int try_op_file(const char *filename, int flags, int mode);
int fatal_op_file(const char *filename, int flags, int mode);

int try_wr_file_raw(int fd, const char *buffer, size_t nbytes);
int fatal_wr_file_raw(int fd, const char *buffer, size_t nbytes);

ssize_t try_read_buffer_raw(int fd, char *buffer, size_t nbytes);
ssize_t fatal_read_buffer_raw(int fd, char *buffer, size_t nbytes);

ssize_t safe_write(int fd, const char *buffer, size_t nbytes);

#endif
