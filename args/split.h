#ifndef SIMPLE_SHELL_SPLIT_H

#define SIMPLE_SHELL_SPLIT_H
#define SH_TOK_BUFSIZE 64
#define SH_TOK_DELIM " \t\r\n\a"

const char **sh_split_line(const char *line);

#endif //SIMPLE_SHELL_SPLIT_H