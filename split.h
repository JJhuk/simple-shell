//
// Created by 이주혁 on 25. 11. 27..
//

#ifndef SIMPLE_SHELL_SPLIT_H
#define SIMPLE_SHELL_SPLIT_H
#define SH_TOK_BUFSIZE 64
#define SH_TOK_DELIM " \t\r\n\a"

char **sh_split_line(char *line);

#endif //SIMPLE_SHELL_SPLIT_H