#include "csapp.h"
void *thread(void *vargp);

int main()
{
    pthread_t tid;
    Pthread_create(&tid, NULL, thread, NULL); // 创建对等线程，执行thread函数
    Pthread_join(tid, NULL); // 主线程等待对等线程终止
    exit(0);
}

void *thread(void *vargp)
{
    printf("Hello, world!\n");
    return NULL;
}