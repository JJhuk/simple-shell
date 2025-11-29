#ifndef SIMPLE_SHELL_BUILTIN_H
#define SIMPLE_SHELL_BUILTIN_H

// char**를 인자로 받고 int를 리턴하는 함수 포인터
typedef int (*builtin_cmd_type)(const char * const *);

builtin_cmd_type get_builtin_cmd(const char *command);

#endif //SIMPLE_SHELL_BUILTIN_H