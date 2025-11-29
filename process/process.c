#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../builtin.h"

void wait_for_pid(const pid_t pid) {
    int status;
    do {
        const pid_t wait = waitpid(pid, &status, 0);
        if (wait == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        // 종료 말고도 signal같은것도 처리해야함.
    } while (!WIFEXITED(status) && !WEXITSTATUS(status));
}

void execute_process(const char * const *args) {
    const builtin_cmd_type builtin_cmd = get_builtin_cmd(args[0]);

    if (builtin_cmd != NULL) {
        builtin_cmd(args);
        exit(EXIT_SUCCESS);
    }

    if (execvp(args[0], (char * const *)args) == -1) {
        perror("sh");
        exit(EXIT_FAILURE);
    }
}
