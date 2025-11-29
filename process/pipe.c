#include "pipe.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "process.h"

void pipe_execute(const char **args, const int pipe_index) {
    // 파이프 뒤에 명령어가 없는 경우 ex) "command |"
    if (args[pipe_index + 1] == NULL) {
        fprintf(stderr, "sh: expected argument to \"|\"\n");
        return;
    }

    // 파이프 앞에 명령어가 없는 경우 ex) "| grep"
    if (pipe_index == 0) {
        fprintf(stderr, "sh: expected argument to \"cd\"\n");
        return;
    }

    args[pipe_index] = NULL;
    const char **cmd1 = args;
    const char **cmd2 = &args[pipe_index + 1];

    int pipe_fd[2];

    if (pipe(pipe_fd) < 0) {
        perror("pipe");
        return;
    }

    const pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("pid1 fork failed");
        return;
    }

    if (pid1 == 0) {
        // child 1
        close(pipe_fd[0]); // 읽기 끝은 필요없음.
        // 표준 출력을 파이프의 쓰기 끝으로 Redirection
        dup2(pipe_fd[1], STDOUT_FILENO);
        // 복제했으므로 원본 fd는 닫음
        close(pipe_fd[1]);

        execute_process(cmd1);
    }

    const pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("pid2 fork failed");
        return;
    }

    if (pid2 == 0) {
        // child 2
        close(pipe_fd[1]);

        // 표준 입력을 파이프의 읽기 끝으로 Redirection
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        execute_process(cmd2);
    }

    // execvp를 성공하든 실패하든 여기는 부모 프로세스만 도달가능.
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    wait_for_pid(pid1);
    wait_for_pid(pid2);
}

int find_pipe_index(const char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            return i;
        }
    }

    return -1;
}