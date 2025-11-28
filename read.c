#include "read.h"

#include <stdio.h>
#include <stdlib.h>

char *sh_read_line(void) {
    int bufSize = SH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufSize);

    if (!buffer) {
        fprintf(stderr, "sh_read_line(): Out of memory\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        const int c = getchar();

        // EOF는 문자가 아니기 때문에 이거 체크 이후에 char로 형변환
        // EOF나 개행을 만나면 null 로 치환하고 문자열을 반환합니다.
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        }

        buffer[position] = (char)c;
        position++;

        // 미리 할당한 버퍼를 넘어가면 재할당
        if (position >= bufSize) {
            bufSize += SH_RL_BUFSIZE;
            char *temp = buffer;
            buffer = realloc(buffer, bufSize);
            if (buffer == NULL) {
                // 재할당 실패하면 buffer가 null이 되어버려 메모리 누수가 발생
                free(temp);
                fprintf(stderr, "sh_read_line(): Out of memory\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
