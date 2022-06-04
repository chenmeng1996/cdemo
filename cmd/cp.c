#include <sys/stat.h>
#include <fcntl.h>
#include "common.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s old-file new-file\n", argv[0]);
        exit(-1);
    }
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1) {
        printf("opening file %s\n", argv[1]);
        exit(-1);
    }
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw-*/
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1) {
        printf("opening file %s\n", argv[2]);
        exit(-1);
    }

    while((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        if (write(outputFd, buf, numRead) != numRead) {
            printf("couldn't write whole buffer\n");
            exit(-1);
        }
    }
    if (numRead == -1) {
        printf("read\n");
        exit(-1);
    }
    if (close(inputFd) == -1) {
        printf("close input\n");
        exit(-1);
    }
    if (close(outputFd) == -1) {
        printf("close output\n");
        exit(-1);
    }
    exit(EXIT_SUCCESS);
}