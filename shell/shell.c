#include "../utils/basic/wcat.h"
#include "fcntl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE_BUFF_SHELL 4096
#define MAX_ARGS 64
static char BUFF_SHELL[SIZE_BUFF_SHELL];
static char LINE_BUFF[SIZE_BUFF_SHELL];
int cd() { return 0; }

int path() { return 0; }

inline int exit_from_shell(int argc, char **argv) { return 0; }

int main(int argc, char **argv) {
  int n = 0;
  int line_idx = 0;
  char *args[MAX_ARGS];
  while (1) {
    write(STDOUT_FILENO, "shell > ", 8);
    if ((n = read(STDIN_FILENO, BUFF_SHELL, SIZE_BUFF_SHELL)) > 0) {
      for (register int i = 0; i < n; i++) {
        if (BUFF_SHELL[i] == '\n') {
          LINE_BUFF[line_idx] = '\0';
          if (line_idx == 0) {
            continue;
          }

          int arg_count = 0;
          char *token = strtok(LINE_BUFF, " \t");

          while (token != NULL && arg_count < MAX_ARGS - 1) {
            args[arg_count++] = token;
            token = strtok(NULL, " \t");
          }
          args[arg_count] = NULL;

          if (arg_count > 0) {
            if (strcmp(args[0], "exit") == 0) {
              exit(0);
            } else if ((strcmp(args[0], "wcat")) == 0) {
              if (args[1]) {
                int fp = open(args[1], O_RDONLY);
                cat(fp);
                close(fp);
              }
            } else {
              pid_t pid = fork();
              if (pid == 0) {
                execvp(args[0], args);
                perror("exec failed");
                exit(1);
              } else if (pid > 0) {
                wait(NULL);
              }
            }
          }
          line_idx = 0;

        } else {
          if (line_idx < SIZE_BUFF_SHELL - 1) {
            LINE_BUFF[line_idx++] = BUFF_SHELL[i];
          }
        }
      }
    } else if (n == 0) {
      break;
    }
  }
  return 0;
}
