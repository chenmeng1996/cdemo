#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main() {
    int fd;
    char template[] = "/tmp/someStringXXXXXX"; // 最后6个字符必须为XXXXXX，这6个字符将被替换。所以是字符数组而非字符串常量。

    fd = mkstemp(template);
    if (fd == -1) {
        exit(-1);
    }
    printf("Generated filename was: %s\n", template);
    unlink(template); // 立刻让该文件名消失，但是在close()后才会删除文件。
    /* 使用该fd进行i/o读写 */
    if (close(fd) == -1) {
        exit(-1);
    }
}