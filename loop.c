#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "loop.h"

#include "builtins.h"
#include "split.h"

void sh_loop(void) {
    int status;

    do {
        printf("> ");
        char *line = sh_read_line();
        char **args = sh_split_line(line);
        status = sh_execute(args);

        free(line);
        free(args);
    } while (status);
}
