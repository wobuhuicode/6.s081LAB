#include "../kernel/types.h"
#include "../user/user.h"

void main(int argc, char *argv[])
{
    int *p = malloc(sizeof(int) * 2);
    char *buf = malloc(sizeof(char) * 10);
    pipe(p);

    int childPid = fork();

    if (childPid != 0) {
        int myPid = getpid();
        read(p[0], buf, 5);
        fprintf(1, "child, myPid %d, receive %s\n", myPid, buf);
        write(p[1], "pong", 5);
    } else {
        int myPid = getpid();
        write(p[1], "ping", 5);
        read(p[0], buf, 5);
        fprintf(1, "parent, myPid, %d, receive %s\n", myPid, buf);
    }

    free(p);

    exit(0);
}