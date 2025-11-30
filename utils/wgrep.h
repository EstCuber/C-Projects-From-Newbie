//
// Created by ivanefremov on 29.11.2025.
//

#ifndef C_PROJECTS_FROM_NEWBIE_WGREP_H
#define C_PROJECTS_FROM_NEWBIE_WGREP_H

#define WGREP_BUFF_SIZE 1024
#define WGREP_LINE_BUFF_SIZE 4096
static char buf[WGREP_BUFF_SIZE];
static char line_buff[WGREP_LINE_BUFF_SIZE];

bool grep(const char *term, int fp);

#endif //C_PROJECTS_FROM_NEWBIE_WGREP_H