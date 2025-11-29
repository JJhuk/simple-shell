#ifndef SIMPLE_SHELL_PROCESS_H
#define SIMPLE_SHELL_PROCESS_H
#include <sys/_types/_pid_t.h>

void wait_for_pid(pid_t pid);
void execute_process(const char * const *args);

#endif //SIMPLE_SHELL_PROCESS_H