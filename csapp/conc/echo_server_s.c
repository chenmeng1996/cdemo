/*
* echo_server_s.c - A concurrent echo server based on select
*/

#include "csapp.h"

typedef struct { // Represents a pool of connected descriptors
    int maxfd; // Largest fd in read_set
    fd_set read_set; // Set of all active descriptors
    fd_set ready_set; // Subset of descriptors ready for reading
    int nready; // Number of ready descriptors from select
    int maxi; // Highwater index into client array
    int clientfd[FD_SETSIZE]; // Set of active descriptors
    rio_t clientrio[FD_SETSIZE]; // Set of active read buffers
} pool;

void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p);
void check_clients(pool *p);

int byte_cnt = 0; // Counts total bytes received by server

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool;

    if (argc != 2) {
        fprintf(stderr, "usgae: %s <port>\n", argv[0]);
        exit(0);
    }

    // 打开一个监听描述符
    listenfd = Open_listenfd(argv[1]);
    init_pool(listenfd, &pool);

    while (1)
    {
        // Wait for listening/connected descriptor(s) to become ready
        pool.ready_set = pool.read_set;
        // 调用Select函数，将进程控制权交给内核
        // 内核监听read_set中是否有可读的fd，如果有，会将fd写入read_set，返回read_set（可读fd集合）
        // 因为会覆盖read_set，为了防止read_set被覆盖，所以构造一个ready_set，专门用来接收就绪的fd
        pool.nready = Select(pool.maxfd+1, &pool.ready_set, NULL, NULL, NULL);

        // 调用FD_ISSET判断哪个fd可读，如果是listen_fd，说明是有新client连接
        // 调用Accept建立连接（生成了conn_fd来表示建立连接），并将连接添加到pool
        if (FD_ISSET(listenfd, &pool.ready_set)) {
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            add_client(connfd, &pool);
        }

        // Echo a text line from each ready connected descriptor
        check_clients(&pool);
    }
    
}

void init_pool(int listenfd, pool *p)
{
    // Initially, there are no connected descriptors
    int i;
    p->maxi = -1;
    for (i=0; i<FD_SETSIZE; i++) {
        p->clientfd[i] = -1;
    }

    // Initially, listenfd is only member of select read set
    p->maxfd = listenfd;
    //创建一个空的read_set
    FD_ZERO(&p->read_set);
    // listenfd添加到read_set
    FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool *p)
{
    int i;
    p->nready--;
    for (i = 0; i < FD_SETSIZE; i++) {
        if (p->clientfd[i] < 0) {
            // Add connected descriptor to pool
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);
        
            // connfd添加到read_set
            FD_SET(connfd, &p->read_set);

            // Update max descriptor and pool highwater mark
            if (connfd > p->maxfd) {
                p->maxfd = connfd;
            }
            if (i > p->maxi) {
                p->maxi = i;
            }
            break;
        }
    }
    if (i == FD_SETSIZE) {
        app_error("add_client error: Too many clients");
    }
}

void check_clients(pool *p)
{
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;
    for (i = 0; (i <= p->maxi) && (p->nready > 0); i++) {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        // If the descriptor is ready, echo a text line from it
        if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set))) {
            p->nready--;
            if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
                byte_cnt += n;
                printf("Server received %d (%d total) bytes on fd %d\n", 
                    n, byte_cnt, connfd);
                Rio_writen(connfd, buf, n);
            }

            // EOF detected, remove descriptor from pool
            else {
                Close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}