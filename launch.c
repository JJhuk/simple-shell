#include "launch.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/proc.h>
#include <unistd.h>

int sh_launch(char **args) {
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
        // parent process

        int status;
        do {
            const pid_t wPid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}