//
// Created by ivanefremov on 30.11.2025.
//

#ifndef C_PROJECTS_FROM_NEWBIE_KEY_VALUE_STORAGE_H
#define C_PROJECTS_FROM_NEWBIE_KEY_VALUE_STORAGE_H

#define KV_BUFFER_SIZE 1024
static char line_buff[4096];
static char buf[1024];

// Example of commands:
// (ofc for linux btw) ./kv {command (get, put or delete)} {file in you will write} {key} {value but not for all commands}

int get(int fp, char *search_key, int is_write);
void put(int fp, char *key, char *value);
void delete(int fp, char *search_key, int is_write, char *filename);

#endif //C_PROJECTS_FROM_NEWBIE_KEY_VALUE_STORAGE_H