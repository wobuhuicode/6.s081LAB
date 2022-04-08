#include "../kernel/types.h"
#include "../kernel/fcntl.h"
#include "../kernel/stat.h"
#include "../kernel/fs.h"
#include "user.h"

char* key;

void find(char *path) {
    char *buf = malloc(sizeof(char) * 100), *p;
    int fd;
    struct dirent de;
    struct stat st;
    

    fd = open(path, O_RDONLY);


    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';

    while (read(fd, &de, sizeof(de)) != 0) {
        if (de.inum == 0) {
            continue;
        }
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;

        if (stat(buf, &st) < 0) {
            printf("cannot stat %s\n", p);
            continue;
        }

        if (st.type == T_FILE && strcmp(p, key) == 0) {
            fprintf(1, "%s\n", buf);
        } else if (
            st.type == T_DIR 
            && strcmp(p, ".") != 0
            && strcmp(p, "..") != 0)
        {
            char *newPath = malloc(sizeof(char) * 100);
            memcpy(newPath, buf, strlen(buf) + 1);
            find(newPath);
        }

    }

    close(fd);

}


void main(int argc, char *args[]) {

    if (argc != 2) {
        fprintf(2, "Error");
        exit(1);
    } else {
        key = args[1];
    }

    find("");

    exit(0);
}