//
// Created by ivanefremov on 29.11.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "wzip.h"

#include "wcat.h"

int zip(int file, int result_file, int* count, char* last_char) {
    bool zipped = false;
    int n;

    while ((n = read(file, buf, WZIP_BUF_SIZE)) > 0) {

        for (int i = 0; i < n; i++) {

            char current_char = buf[i];

            if (*count == 0) {
                *last_char = current_char;
            }

            if (current_char == *last_char) {
                (*count)++;
            }
            else {
                write(result_file, count, sizeof(int));
                write(result_file, last_char, sizeof(char));

                *count = 1;
                *last_char = current_char;
            }
        }
    }
}

int main(int argc, char **argv) {
    int fp_in, fp_out;
    char last_char;
    int count = 0;


    if (argc <= 2) {
        printf("wzip: incorrect call, call in format {wzip file_in file_out}");
        exit(1);
    }

    if ((fp_out = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        printf("wzip: cannot open %s\n", argv[argc-1]);
        exit(1);
    }
    for (int i = 1; i < argc-1; i++) {
        if ((fp_in = open(argv[i], O_RDONLY)) < 0) {
            printf("wzip: cannot open %s\n", argv[i]);
            exit(1);
        }
        zip(fp_in, fp_out, &count, &last_char);
        close(fp_in);
    }

    if (count > 0) {
        write(fp_out, &count, sizeof(int));
        write(fp_out, &last_char, sizeof(char));
    }

    close(fp_out);
    exit(0);
}