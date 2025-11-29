#ifndef SIMPLE_SHELL_PIPE_H
#define SIMPLE_SHELL_PIPE_H

void pipe_execute(const char **args, int pipe_index);
int find_pipe_index(const char **args);

#endif //SIMPLE_SHELL_PIPE_H