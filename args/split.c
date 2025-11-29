#include "split.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char **sh_split_line(const char *line) {
    int bufSize = SH_TOK_BUFSIZE;
    int position = 0;
    const char **tokens = malloc(bufSize * sizeof(char *));

    if (!tokens) {
        fprintf(stderr, "Error allocating memory for tokens\n");
        exit(EXIT_FAILURE);
    }

    const char *token = strtok((char *)line, SH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufSize) {
            bufSize += SH_TOK_BUFSIZE;
            const char **temp = tokens;
            tokens = realloc(tokens, bufSize * sizeof(char *));
            if (!tokens) {
                free(temp);
                fprintf(stderr, "Error reallocating memory for tokens\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, SH_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}
