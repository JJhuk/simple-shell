#ifndef SIMPLE_SHELL_PROCESS_H
#define SIMPLE_SHELL_PROCESS_H
#include <sys/types.h>

void wait_for_pid(pid_t pid);
void execute_process(const char * const *args);

#endif //SIMPLE_SHELL_PROCESS_H