//
// Created by ivanefremov on 01.12.2025.
//

#ifndef C_PROJECTS_FROM_NEWBIE_REVERSE_H
#define C_PROJECTS_FROM_NEWBIE_REVERSE_H

#define REVERSE_BUFF_SIZE 1024
#define REVERSE_LINE_BUFF 4096
static char buf[REVERSE_BUFF_SIZE];
static char line_buff[REVERSE_BUFF_SIZE];

// two flags (must have!)
// 1. -half (reverse only the order of lines)
// 2. -full (reverse order and lines)
// for using need to compile this and after that (on linux) use ./reverse hello.txt -half (for example)
void reverse(int fp, char* _flag);

#endif //C_PROJECTS_FROM_NEWBIE_REVERSE_H