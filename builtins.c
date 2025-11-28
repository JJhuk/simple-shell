#include "builtins.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <__stddef_null.h>

#include "launch.h"

const char *builtin_str[] = {"cd", "help", "exit"};
int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);

int (*builtin_func[]) (char**) = {
    &sh_cd,
    &sh_help,
    &sh_exit,
};

int sh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

int sh_cd(char **args) {
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

int sh_help(char **args) {
    printf("sh\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (int i = 0; i < sh_num_builtins(); i++) {
        printf("    %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int sh_exit(char **args) {
    return 0;
}

int sh_execute(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    for (int i = 0; i < sh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return sh_launch(args);
}