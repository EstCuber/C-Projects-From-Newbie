//
// Created by ivanefremov on 01.12.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "reverse.h"

#include <string.h>

// По возможности переписать под разные флаги!
void reverse(int fp, char* _flag) {
    lseek(fp, 0, SEEK_SET);
    int result_file = open("reversed_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int n;
    int line_idx = 0;

    while ((n = read(fp, buf, REVERSE_BUFF_SIZE)) > 0) {
        for (int i = n -1; i >= 0; i--) {
            if (buf[i] == '\n') {
                line_buff[line_idx] = '\0';
                if ((strcmp(_flag, "-half")) == 0) {
                    for (int j = line_idx - 1; j >= 0; --j) {
                        write(result_file, &line_buff[j], 1);
                    }
                    write(result_file, "\n", 1);
                    line_idx = 0;
                } else if ((strcmp(_flag, "-full")) == 0) {
                    write(result_file, line_buff, strlen(line_buff));
                    write(result_file, "\n", 1);
                    line_idx = 0;
                }
            }
            else {
                if (line_idx < sizeof(line_buff) - 1) {
                    line_buff[line_idx++] = buf[i];
                }
            }
        }
    }
    if (line_idx > 0) {
        if ((strcmp(_flag, "-half")) == 0) {
            for (int j = line_idx - 1; j >= 0; --j) {
                write(result_file, &line_buff[j], 1);
            }
            write(result_file, "\n", 1);
        } else if ((strcmp(_flag, "-full")) == 0) {
            line_buff[line_idx] = '\0';
            write(result_file, line_buff, line_idx);
            write(result_file, "\n", 1);
        }
    }
}

int main (int argc, char *argv[]) {
    int fp;
    if (argc <= 2) {
        printf("reverse: error with args");
        exit(1);
    }

    if ((fp = open(argv[1], O_RDONLY)) == -1) {
        printf("reverse: error with open");
        exit(1);
    }

    reverse(fp, argv[2]);
    close(fp);
    exit(0);
}