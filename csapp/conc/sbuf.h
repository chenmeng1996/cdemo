#include <semaphore.h>

typedef struct {
    int *buf; // 缓冲数组
    int n; // 槽的最大数量
    int front; // buf[(front+1)%n]是第一个元素
    int rear; // buf[read%n]是最后一个元素
    sem_t mutex; // 保护对buf的访问
    sem_t slots; // 可用的槽的数量
    sem_t items; // 可用的元素的数量
} sbuf_t;

void sbuf_init(sbuf_t *sp, int n);
void sbuf_deinit(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp, int item);
int sbuf_remove(sbuf_t *sp);