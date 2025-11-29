//
// Created by ivanefremov on 29.11.2025.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#define WGREP_BUFF_SIZE 1024
#define WGREP_LINE_BUFF_SIZE 4096
static char buf[WGREP_BUFF_SIZE];
static char line_buff[WGREP_LINE_BUFF_SIZE];

bool grep(const char *term, int fp) {
    int n;
    bool finded = false;
    int line_idx = 0;

    while ((n = read(fp, buf, WGREP_BUFF_SIZE)) > 0) {
        for (int i = 0; i < n; i++) {
            char current_char = buf[i];
            if (buf[i] == '\n') {
                line_buff[line_idx++] = '\n';
                line_buff[line_idx] = '\0';

                if (strstr(line_buff, term) != NULL) {
                    write(STDOUT_FILENO, line_buff, line_idx);
                    finded = true;
                }

                line_idx = 0;
            }
            else {
                line_buff[line_idx++] = current_char;
                if (line_idx >= sizeof(line_buff)-1) {
                    line_idx = 0;
                }
            }
        }
    }

    if (line_idx > 0) {
        line_buff[line_idx] = '\0';
        if (strstr(line_buff, term) != NULL) {
            write(STDOUT_FILENO, line_buff, line_idx);
            write(STDOUT_FILENO, "\n", 1);
            finded = true;
        }
    }
    return finded;
}


int main(int argc, char *argv[]) {
    int fp;
    bool grepped = false;
    // check value of args
    if (argc <= 1) {
        printf("wgrep: write pattern which need to search");
        exit(1);
    }
    char *pattern = argv[1];
    if (argc == 2) {
        grepped = grep(pattern, STDIN_FILENO);
    } else {
        for (int i = 2; i < argc; i++) {
            if ((fp = open(argv[i], O_RDONLY)) < 0) {
                printf("wgrep: cannot open %s\n", argv[i]);
                exit(1);
            }
            grepped = grep(pattern, fp);
            close(fp);
        }
    }

    if (grepped == true) {
        exit(0);
    } else {
        printf("wgrep: didn't find the pattern\n");
        exit(0);
    }
}