#include "../kernel/types.h"
#include "user.h"


char *readLine() {
    char *buf = malloc(sizeof(char) * 100);
    char *p = buf;
    buf[0] = '\0';
    while (read(0, p, 1) != 0) {
        if (*p == '\n') {
            *p = '\0';
            break;
        }
        p++;
    }

    return buf;
}

void execCmd(char *cmdAndArgs[]) {
    int pid = fork();
    if (pid == 0) exec(cmdAndArgs[0], cmdAndArgs);
}


void main(int argc, char *args[]) {
    char** cmdAndArgs = malloc(sizeof(char*) * 10);
    int st;
    for (int i = 0; i < argc - 1; i++) {
        cmdAndArgs[i] = args[i + 1];
    }

    char* line = readLine();
    while (line[0] != '\0') {
        cmdAndArgs[argc - 1] = line;
        cmdAndArgs[argc] = 0;
        execCmd(cmdAndArgs);
        wait(&st);
        line = readLine();
    }
    
    exit(0);
}