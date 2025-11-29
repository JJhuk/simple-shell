#ifndef SIMPLE_SHELL_HISTORY_H

#define SIMPLE_SHELL_HISTORY_H
#define HISTORY_SIZE 100 // 저장할 명령어 개수
#define CMD_MAX_LEN 1024 // 명령어 최대 길이
#include <semaphore.h>

typedef struct {
    int head;
    int count;
    char commands[HISTORY_SIZE][CMD_MAX_LEN];
} history_shm_t;

extern history_shm_t *history_shm;
extern sem_t *history_sem;

void init_history();
void add_history(const char *cmd);

#endif //SIMPLE_SHELL_HISTORY_H