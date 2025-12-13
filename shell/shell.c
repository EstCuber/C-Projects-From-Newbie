#include "shell.h"
#include "../utils/basic/wcat.h"
#include "fcntl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int cd() { return 0; }

int path() { return 0; }

// inline int exit_from_shell(char *arg) {
//   if (strcmp(arg, "exit") == 0) {
//     exit(0);
//   }
//   return -1;
// }

int shell(int argc, char **argv) {
  int n = 0;
  int line_idx = 0;
  char *args[MAX_ARGS];
  // бесконечный цикл т.к шелл
  while (1) {
    // выводим в дескриптор вывода shell >
    write(STDOUT_FILENO, "shell > ", 8);
    // читаем то что нам вводят, читаем в буффер
    if ((n = read(STDIN_FILENO, BUFF_SHELL, SIZE_BUFF_SHELL)) > 0) {
      // возможно ускорит если ему обозначить класть его в регистр? для
      // ускорения чтения строки
      for (register int i = 0; i < n; i++) {
        // для конца строки
        if (BUFF_SHELL[i] == '\n') {
          LINE_BUFF[line_idx] = '\0';
          // если пользователь ничего не ввел
          if (line_idx == 0) {
            continue;
          }

          // количество аргументов
          int arg_count = 0;
          // strtok - функция, которая выделяет слова до разделителя, в нашем
          // случае мы заполняем аргументы
          char *token = strtok(LINE_BUFF, " \t");

          while (token != NULL && arg_count < MAX_ARGS - 1) {
            args[arg_count++] = token;
            token = strtok(NULL, " \t");
          }
          args[arg_count] = NULL;

          // если количество аргументов больше нуля, начинаем сверку
          if (arg_count > 0) {
            if (strcmp(args[0], "exit") == 0) {
              exit(0);
            } else if ((strcmp(args[0], "wcat")) == 0) {
              // ну вообще можно было реализовать это и в wcat
              if (args[1]) {
                int fp = open(args[1], O_RDONLY);
                cat(fp);
                close(fp);
              }
            } else {
              // создаю дочерний процесс, который и выполнит то что мы в
              // аргументе ввели, при условии что он не совпал ни с одним из
              // заготовленных
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
          // заполняем LINE_BUFF
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

int main(int argc, char **argv) { shell(argc, argv); }
