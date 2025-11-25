//
// Created by ivanefremov on 25.11.2025.
//

#include "wcat.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define WCAT_BUFF_SIZE 1024
static char buf[WCAT_BUFF_SIZE];

void cat(int file) {
    int n;

    while ((n = read(file, buf, sizeof(buf))) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            printf("wcat: error write");
            exit(1);
        }

    }

    if (n < 0) {
        printf("wcat: cannot open file\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {

    int fp, i;

    if (argc <= 1) {
        exit(0);
    }

    for (i = 1; i < argc; i++) {
        if ((fp = open(argv[i], O_RDONLY)) < 0) {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        cat(fp);
        close(fp);
    }

    exit(0);
}