#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t fpid;
    int count = 0;

    fpid = fork();

    if (fpid < 0)
        printf("创建进程失败");
    else if(fpid == 0) {
        printf("我是子进程\n");
        count++;
    } else {
        printf("我是父进程\n");
        count++;
    }
    printf("统计结果：%d\n", count);
}