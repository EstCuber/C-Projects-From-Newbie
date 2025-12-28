//
// Created by ivanefremov on 30.11.2025.
//

#include "wunzip.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

void unzip(int file) {
    int count;
    while ((read(file, &count, sizeof(int))) > 0) {
        read(file, buf, 1);

        for (int i = 0; i < count; i++) {
            printf("%c", buf[0]);
        }
    }


}

int main(int argc, char **argv) {
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            int fp = open(argv[i], O_RDONLY);

            if (fp < 0) {
                printf("wunzip: error to open");
                exit(1);
            }

            unzip(fp);
            close(fp);
        }

    exit(0);
    } else {
        printf("wunzip: error with args");
        exit(1);
    }
}