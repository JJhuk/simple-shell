#include "builtin.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char *builtin_str[] = {"cd", "help", "exit"};

int sh_cd(const char * const *args) {
    if (args[1] == NULL) {
        fprintf(stderr, "sh: expected argument to \"cd\"\n");
    }

    else {
        if (chdir(args[1]) != 0 ) {
            perror("sh");
        }
    }

    return 1;
}

int sh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

int sh_help(const char * const *args) {
    printf("sh\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (int i = 0; i < sh_num_builtins(); i++) {
        printf("    %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int sh_exit(const char * const *args) {
    return 0;
}

builtin_cmd_type builtin_func[] = {
    &sh_cd,
    &sh_help,
    &sh_exit,
};

builtin_cmd_type get_builtin_cmd(const char *command) {
    for (int i = 0; i < sh_num_builtins(); i++) {
        if (strcmp(command, builtin_str[i]) == 0) {
            return builtin_func[i];
        }
    }

    return NULL;
}
