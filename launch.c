#include "launch.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/proc.h>
#include <unistd.h>

#include "process/process.h"

int sh_launch(const char * const *args) {
    const pid_t pid = fork();

    if (pid == 0) {
        // child process

        if (execvp(args[0], args) == -1) {
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
