#include "history.h"
#include <stddef.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h> // fstat 사용을 위해 추가

#define SHM_NAME "/sh_history_mem" // 공유 메모리 이름
#define SEM_NAME "/lsh_sem_lock"

history_shm_t *history_shm = NULL;
sem_t *history_sem = NULL;

void init_history() {
    // 세마포어를 열거나 생성
    history_sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);

    if (history_sem == SEM_FAILED) {
        perror("sem_open");
        munmap(history_shm, sizeof(history_shm_t));
        history_shm = NULL;
        exit(EXIT_FAILURE);
    }

    sem_wait(history_sem);

    // 읽기/쓰기 모드로 공유 메모리 객체를 열거나 생성
    const int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // 공유 메모리 객체의 상태(크기)를 확인
    struct stat shm_stat;
    if (fstat(shm_fd, &shm_stat) == -1) {
        perror("fstat");
        close(shm_fd);
        exit(EXIT_FAILURE);
    }

    const int is_new = shm_stat.st_size == 0;

    // 새로 생성된 공유 메모리인 경우에만 크기를 설정
    if (is_new) {
        if (ftruncate(shm_fd, sizeof(history_shm_t)) == -1) {
            perror("ftruncate");
            close(shm_fd);
            exit(EXIT_FAILURE);
        }
    }

    // 공유 메모리를 현재 프로세스의 주소 공간에 매핑
    history_shm = mmap(NULL, sizeof(history_shm_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (history_shm == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        exit(EXIT_FAILURE);
    }

    // mmap이 완료되면 파일 디스크립터는 더 이상 필요 없으므로 닫아줍니다.
    close(shm_fd);

    // 새로 생성된 공유 메모리인 경우, 내부 변수들을 초기화
    if (is_new) {
        history_shm->head = 0;
        history_shm->count = 0;
    }

    sem_post(history_sem);
}

void add_history(const char *cmd) {
    if (history_shm == NULL || cmd == NULL || history_sem == NULL) {
        return;
    }

    // 비어있는 명령어는 히스토리에 추가하지 않음
    if (strlen(cmd) == 0) {
        return;
    }

    sem_wait(history_sem);

    // head 위치에 명령어 복사
    strncpy(history_shm->commands[history_shm->head], cmd, CMD_MAX_LEN - 1);
    history_shm->commands[history_shm->head][CMD_MAX_LEN - 1] = '\0';

    history_shm->head = (history_shm->head + 1) % HISTORY_SIZE;

    if (history_shm->count < HISTORY_SIZE) {
        history_shm->count++;
    }

    sem_post(history_sem);
}