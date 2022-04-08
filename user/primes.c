#include "../kernel/types.h"
#include "user.h"

void main(int argc, char* args[]) {
    int *p = malloc(sizeof(int) * 2);
    pipe(p);

    int pid = fork();

    if (pid != 0) {
        close(p[0]);
        for (int i = 2; i <= 53; i++) {
            int temp = i;
            write(p[1], &temp, 4);
        }
        close(p[1]);
        int *status = malloc(sizeof(int));
        wait(status);
        exit(*status);
    } else {
        while (pid == 0) {
            close(p[1]);
            int *buf = malloc(sizeof(int));
            int *prime = malloc(sizeof(int));
            int *tempPipe = malloc(sizeof(int) * 2);
            int flag = 0; // 标志是否还有子进程
            pipe(tempPipe);
            

            read(p[0], prime, 4);
            fprintf(1, "prime %d\n", *prime);

            while (read(p[0], buf, 4) != 0) {
                if (*buf % *prime != 0) {
                    write(tempPipe[1], buf, 4);
                    flag = 1;
                }
            }
            
            close(p[0]);
            free(p);

            if (flag == 1) {
                pid = fork();
                p = tempPipe;
                if (pid != 0) {
                    close(p[0]);
                    close(p[1]);
                    int *status = malloc(sizeof(int));
                    wait(status);
                    exit(*status);
                }
            } else {
                close(tempPipe[0]);
                close(tempPipe[1]);
                exit(0);
            }

        }
    }

    exit(0);
}
