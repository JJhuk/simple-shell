#include "launch.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "process/process.h"

int sh_launch(const char * const *args) {
    const pid_t pid = fork();

    if (pid == 0) {
        // child process

        if (execvp(args[0], (char * const *)args) == -1) {
            perror("sh");
        }

        exit(EXIT_FAILURE);
    }
    if (pid < 0) {
        // error forking
        perror("fork");
    }
    else {
        wait_for_pid(pid);
    }

    return 1;
}
