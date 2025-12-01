//
// Created by ivanefremov on 30.11.2025.
//

#include "key_value_storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int get(int fp, char *search_key, int is_write) {
    // Алгоритм - получаем строку,
    // Разделяем строку по запятым (находим запятую, сохраняем полученное значение до нее и после)
    // Сравнить с помощью strcmp

    int n;
    int line_idx = 0;
    while ((n = read(fp, buf, KV_BUFFER_SIZE)) > 0) {
        for (int i = 0; i < n; i++) {
            if (buf[i] == '\n') {
                line_buff[line_idx++] = '\0';
                char *comma_pos = strchr(line_buff, ',');

                if (comma_pos != NULL) {
                    *comma_pos = '\0';

                    char *file_key = line_buff;
                    char *file_value = comma_pos + 1;

                    if ((strcmp(file_key, search_key)) == 0) {
                        if (is_write == 0) {
                            printf("key = %s, value = %s\n", file_key, file_value);
                        }
                            return 0;
                    }
                }
                line_idx = 0;

            } else {
                if (line_idx < sizeof(line_buff) - 1) {
                    line_buff[line_idx++] = buf[i];
                }
            }
        }
    }
    return -1;
}


void put(int fp, char*key, char* value) {

    if ((get(fp, key, 0)) == 0) {
        printf("key already exists!\n");
        return;
    }
    write(fp, key, sizeof(char) * strlen(key));
    write(fp, ",", sizeof(char));
    write(fp, value, sizeof(char)*strlen(value));
    write(fp, "\n", sizeof(char));
}



void delete(int fp, int key, char* value) {

}

int main(int argc, char **argv) {
    int fp;
    if (argc <= 2) {
        printf("kv: not right format!\n");
        exit(1);
    }

    if (argc >= 3) {
        if (strcmp(argv[1], "get") == 0) {
            if ((fp = open(argv[2], O_RDONLY)) != 0) {
                char *search_key = argv[3];
                get(fp, search_key, 0);
                close(fp);
            } else {
                printf("kv: file not found!\n");
                exit(1);
            }
        }
        else if (strcmp(argv[1], "put") == 0) {
            if ((fp = open(argv[2], O_RDWR | O_CREAT | O_APPEND, 0644)) != -1) {
                ;
                char *key = argv[3];
                char *value = argv[4];
                put(fp, key, value);
                close(fp);
            } else {
                printf("kv: Error with open file!");
                exit(1);
            }
        } else {
            printf("kv: not right arguments\n");
            exit(1);
        }
    }

    exit(0);
}