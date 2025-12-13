#ifndef C_PROJECTS_FROM_NEWBIE_BASELIB_FILE
#define C_PROJECTS_FROM_NEWBIE_BASELIB_FILE

#include <stddef.h>
#include <string.h>

#define try_wr_file_str(fd, buffer) try_wr_file_raw(fd, buffer, strlen(buffer))
#define fatal_wr_file_str(fd, buffer)                                          \
  fatal_wr_file_raw(fd, buffer, strlen(buffer))

#define try_create_file(filename, flags) try_op_file(filename, flags, 0644)
#define try_read_file(filename, flags) try_op_file(filename, flags, 0)
#define fatal_create_file(filename, flags) fatal_op_file(filename, flags, 0644)
#define fatal_read_file(filename, flags) fatal_op_file(filename, flags, 0)

int try_op_file(char *filename, int flags, int mode);
int fatal_op_file(char *filename, int flags, int mode);

int try_wr_file_raw(int fd, const char *buffer, size_t nbytes);
int fatal_wr_file_raw(int fd, const char *buffer, size_t nbytes);

#endif
