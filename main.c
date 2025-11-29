#include <stdio.h>
#include <stdlib.h>
#include "launch.h"
#include "args/read.h"
#include "args/split.h"
#include "builtin.h"
#include "history.h"
#include "process/pipe.h"

void sh_loop(void);
int sh_execute(const char **args);

int main(void) {
    // init
    init_history();

    // Run command Loop
    sh_loop();

    // perform any shutdown/cleanup
    return EXIT_SUCCESS;
}

void sh_loop(void) {
    int status;

    do {
        printf("> ");

        const char *line = sh_read_line();
        const char **args = sh_split_line(line);

        status = sh_execute(args);

        add_history(line);

        free((void *)line);
        free((void **)args);
    } while (status);
}

int sh_execute(const char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    const int pipe_index = find_pipe_index(args);

    // 파이프 없는 버전
    if (pipe_index == -1) {
        const builtin_cmd_type builtin_cmd = get_builtin_cmd(args[0]);
        if (builtin_cmd != NULL) {
            return builtin_cmd(args);
        }

        return sh_launch(args);
    }

    pipe_execute(args, pipe_index);
    return 1;
}
