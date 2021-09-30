#include "csapp.h"
#define N 2
void *thread(void *vargp);

char **ptr; // 全局变量

int main()
{
    int i;
    pthread_t tid;
    char *msgs[N] = {
        "Hello from foo",
        "Hello from bar"
    };

    ptr = msgs;
    for (i = 0; i < N; i++) {
        // int可以转换成通用指针
        Pthread_create(&tid, NULL, thread, (void *)i);
    }
    Pthread_exit(NULL);
}

void *thread(void *vargp)
{
    printf("%p\n", &vargp); // vargp是一个int值，内存地址不一样，这里没有数据竞争。
    // 通用指针再转成int
    int myid = (int)vargp; 
    static int cnt = 0; // 本地静态变量，所有线程共享一个实例，有数据竞争。
    printf("[%d]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
    return NULL;
}